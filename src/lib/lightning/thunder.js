// Synthesised thunder (no audio files): a filtered brown-noise rumble with a sharp crack for
// close strikes. Browsers only allow audio after a user gesture, so `unlockAudio` must be
// called from a click/keypress before `thunder` will make a sound.

let ctx = null;

export function unlockAudio() {
    try {
        const AC = window.AudioContext || window.webkitAudioContext;
        if (!AC) return;
        ctx ??= new AC();
        if (ctx.state === 'suspended') ctx.resume();
    } catch {
        ctx = null;
    }
}

function noiseBuffer(seconds, brown) {
    const length = Math.floor(ctx.sampleRate * seconds);
    const buffer = ctx.createBuffer(1, length, ctx.sampleRate);
    const data = buffer.getChannelData(0);
    let last = 0;
    for (let i = 0; i < length; i++) {
        const white = Math.random() * 2 - 1;
        if (brown) {
            last = (last + 0.02 * white) / 1.02;
            data[i] = last * 3.5;
        } else {
            data[i] = white;
        }
    }
    return buffer;
}

/** @param {number} distance 0 (overhead) .. 1 (far away) */
export function thunder(distance = 0.5, volume = 0.5) {
    if (!ctx || ctx.state !== 'running') return;
    const now = ctx.currentTime;
    const delay = 0.12 + distance * 1.1; // sound arrives after the flash
    const duration = 2.6 + distance * 2.2;
    const peak = volume * (1 - distance * 0.55);

    const out = ctx.createGain();
    out.gain.value = 1;
    out.connect(ctx.destination);

    // Rumble
    const rumble = ctx.createBufferSource();
    rumble.buffer = noiseBuffer(duration, true);
    const lowpass = ctx.createBiquadFilter();
    lowpass.type = 'lowpass';
    lowpass.frequency.setValueAtTime(900 - distance * 600, now + delay);
    lowpass.frequency.exponentialRampToValueAtTime(110, now + delay + duration);
    const rumbleGain = ctx.createGain();
    const g = rumbleGain.gain;
    g.setValueAtTime(0.0001, now);
    g.setValueAtTime(0.0001, now + delay);
    g.exponentialRampToValueAtTime(peak, now + delay + 0.05);
    // A few rolling swells as the sound reflects off the terrain
    let t = now + delay + 0.25;
    let level = peak * 0.7;
    while (t < now + delay + duration * 0.7) {
        g.exponentialRampToValueAtTime(Math.max(level * (0.45 + Math.random() * 0.5), 0.0002), t);
        t += 0.25 + Math.random() * 0.45;
        level *= 0.78;
    }
    g.exponentialRampToValueAtTime(0.0001, now + delay + duration);
    rumble.connect(lowpass).connect(rumbleGain).connect(out);
    rumble.start(now);
    rumble.stop(now + delay + duration + 0.1);

    // Crack (only for nearby strikes)
    if (distance < 0.45) {
        const crack = ctx.createBufferSource();
        crack.buffer = noiseBuffer(0.4, false);
        const highpass = ctx.createBiquadFilter();
        highpass.type = 'highpass';
        highpass.frequency.value = 900;
        const crackGain = ctx.createGain();
        crackGain.gain.setValueAtTime(0.0001, now + delay);
        crackGain.gain.exponentialRampToValueAtTime(peak * 0.6, now + delay + 0.01);
        crackGain.gain.exponentialRampToValueAtTime(0.0001, now + delay + 0.35);
        crack.connect(highpass).connect(crackGain).connect(out);
        crack.start(now + delay);
        crack.stop(now + delay + 0.4);
    }
}
