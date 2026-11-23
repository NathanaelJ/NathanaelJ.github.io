// Canvas renderer for lightning strikes. A strike grows as a stepped leader, then the main
// channel lights up at a steady brightness and slowly fades. Bolts are pinned to the page,
// so they scroll with whatever they hit.
import { makeBolt } from './bolt.js';
import { thunder } from './thunder.js';

// Elements lightning likes to attach to (extremities, in aircraft-zoning terms)
export const ATTACHABLE = [
    '.introimg',
    '.name',
    'h1',
    'h2',
    'h3',
    '.position',
    '.project-card',
    '.project-link',
    '.apple-button',
    '.download-btn',
    '.menu-links',
    '.storm-toggle',
    '.image-container img',
    'figure img'
].join(',');

// Glow layers, outermost first: [width multiplier, rgb, alpha]
const LAYERS = [
    [20, '40, 110, 255', 0.1],
    [8, '70, 140, 255', 0.3],
    [3.2, '175, 210, 255', 0.85],
    [1.4, '255, 255, 255', 1]
];

const HOLD = 1300; // ms at (slowly decaying) full brightness after attachment
const FADE = 700; // ms to fade out afterwards

const clamp = (v, lo, hi) => Math.min(hi, Math.max(lo, v));

export class LightningEngine {
    constructor(canvas) {
        this.canvas = canvas;
        this.ctx = canvas.getContext('2d');
        this.bolts = [];
        this.running = false;
        this.width = 0;
        this.height = 0;
        this.reducedQuery = window.matchMedia('(prefers-reduced-motion: reduce)');

        this.frame = this.frame.bind(this);
        this.resize = this.resize.bind(this);
        this.onScroll = () => this.start();

        this.resizeObserver = new ResizeObserver(this.resize);
        this.resizeObserver.observe(canvas);
        window.addEventListener('scroll', this.onScroll, { passive: true });
        this.resize();
    }

    destroy() {
        this.resizeObserver.disconnect();
        window.removeEventListener('scroll', this.onScroll);
        this.bolts = [];
    }

    get reduced() {
        return this.reducedQuery.matches;
    }

    resize() {
        const { width, height } = this.canvas.getBoundingClientRect();
        if (!width || !height) return;
        // A width change reflows the page, so bolts pinned to page positions would be wrong.
        // (Height-only changes happen constantly on phones as the URL bar shows/hides.)
        if (this.width && Math.abs(width - this.width) > 1) this.bolts = [];
        this.width = width;
        this.height = height;
        // Cap the backing store at ~9 megapixels so huge/high-DPI screens stay smooth
        this.dpr = Math.min(window.devicePixelRatio || 1, 2, Math.sqrt(9e6 / (width * height)));
        this.canvas.width = Math.round(width * this.dpr);
        this.canvas.height = Math.round(height * this.dpr);
        // Everything is sized relative to the screen
        const short = Math.min(width, height);
        this.scale = clamp(short / 700, 0.55, 1.5);
        this.step = clamp(short / 30, 10, 30);
        this.start();
    }

    /** Pick a visible element to strike at random. */
    strikeRandom(opts = {}) {
        const candidates = [...document.querySelectorAll(ATTACHABLE)].filter((el) => {
            const r = el.getBoundingClientRect();
            return (
                r.width > 16 &&
                r.height > 8 &&
                r.top > this.height * 0.04 &&
                r.top < this.height * 0.92 &&
                r.left > -r.width / 2 &&
                r.right < this.width + r.width / 2 &&
                getComputedStyle(el).visibility !== 'hidden'
            );
        });
        if (!candidates.length) return;
        this.strike(candidates[Math.floor(Math.random() * candidates.length)], opts);
    }

    /**
     * @param {Element | {x: number, y: number}} target element, or a viewport point
     * @param {{ sound?: boolean, dim?: number }} opts dim: how much to darken the page (0..1)
     */
    strike(target, { sound = false, dim = 0.32 } = {}) {
        if (!this.width) return;
        // Never more than ~3 strikes per second, however fast someone clicks
        const t = performance.now();
        if (t - (this.lastStrike ?? -Infinity) < 340) return;
        const el = target instanceof Element ? target : null;
        const [x1, y1] = el ? this.attachPoint(el) : [target.x, target.y];
        if (!(y1 > 0 && y1 < this.height && x1 > 0 && x1 < this.width)) return;
        this.lastStrike = t;

        const spread = Math.min(this.width * 0.5, 600);
        const x0 = clamp(x1 + (Math.random() - 0.5) * spread, this.width * 0.04, this.width * 0.96);
        const geom = makeBolt({ from: [x0, -12], to: [x1, y1], step: this.step });

        const reduced = this.reduced;
        const leaderDur = reduced ? 0 : clamp(160 + geom.length * 12, 220, 520);
        this.bolts.push({
            geom,
            born: t,
            leaderDur,
            returnAt: t + leaderDur,
            scrollRef: window.scrollY,
            dim: reduced ? 0 : dim
        });

        setTimeout(() => {
            if (el) this.zap(el);
            if (sound) thunder(0.15 + Math.random() * 0.7);
        }, leaderDur);
        this.start();
    }

    attachPoint(el) {
        const r = el.getBoundingClientRect();
        if (el.matches('.introimg')) {
            // Round portrait: hit the top of the circle, slightly off-centre
            const radius = r.width / 2;
            const dx = (Math.random() - 0.5) * radius * 0.8;
            return [r.left + radius + dx, r.top + radius - Math.sqrt(radius * radius - dx * dx) + 2];
        }
        const x = r.left + r.width * (0.2 + Math.random() * 0.6);
        return [clamp(x, 4, this.width - 4), clamp(r.top + Math.min(3, r.height * 0.1), 4, this.height - 4)];
    }

    zap(el) {
        el.classList.remove('lightning-struck');
        void el.offsetWidth; // restart the CSS animation
        el.classList.add('lightning-struck');
        clearTimeout(el._lightningTimer);
        el._lightningTimer = setTimeout(() => el.classList.remove('lightning-struck'), 1200);
    }

    start() {
        if (!this.running) {
            this.running = true;
            requestAnimationFrame(this.frame);
        }
    }

    frame() {
        const now = performance.now();
        const { ctx, width, height } = this;
        ctx.setTransform(this.dpr, 0, 0, this.dpr, 0, 0);
        ctx.clearRect(0, 0, width, height);

        this.bolts = this.bolts.filter((b) => now < b.returnAt + HOLD + FADE);

        // Gentle storm darkening while the leader descends, easing away after attachment
        let darkness = 0;
        for (const b of this.bolts) {
            const k = now < b.returnAt ? (now - b.born) / b.leaderDur : 1 - (now - b.returnAt) / (HOLD + FADE);
            darkness = Math.max(darkness, b.dim * Math.sin((clamp(k, 0, 1) * Math.PI) / 2));
        }
        if (darkness > 0.001) {
            ctx.fillStyle = `rgba(8, 16, 46, ${darkness})`;
            ctx.fillRect(0, 0, width, height);
        }

        for (const b of this.bolts) {
            ctx.save();
            // Pinned to the page: follow the scroll
            ctx.translate(0, b.scrollRef - window.scrollY);
            this.drawBolt(b, now);
            ctx.restore();
        }

        if (this.bolts.length) requestAnimationFrame(this.frame);
        else {
            ctx.clearRect(0, 0, width, height);
            this.running = false;
        }
    }

    /** Steady brightness that decays slowly, then fades out. */
    intensity(b, now) {
        const age = now - b.returnAt;
        if (age < 150) return 0.6 + 0.4 * (age / 150); // brighten smoothly from the leader
        if (age < HOLD) return 1 - 0.3 * (age / HOLD);
        return 0.7 * Math.max(0, 1 - (age - HOLD) / FADE);
    }

    drawBolt(b, now) {
        const { ctx, scale } = this;
        const { main, branches, length } = b.geom;

        if (now < b.returnAt) {
            // Stepped leader: grow the channel and its branches step by step
            const progress = ((now - b.born) / b.leaderDur) * length;
            for (const br of branches) this.strokeLayers(grow(br.pts, progress), scale * (0.5 / br.depth), 0.5);
            this.strokeLayers(grow(main, progress), scale * 0.7, 0.6);
            return;
        }

        const I = this.intensity(b, now);
        // Branches don't carry the return stroke: they fade out gently
        const branchFade = 0.55 * Math.max(0, 1 - (now - b.returnAt) / 600);
        if (branchFade > 0) {
            for (const br of branches) this.strokeLayers(br.pts, scale * (0.6 / br.depth), branchFade);
        }
        this.strokeLayers(main, scale * (0.7 + 0.3 * Math.min(1, (now - b.returnAt) / 150)), I);

        // Soft glow where the channel meets the page
        const end = main[main.length - 1];
        const r = 14 * scale;
        const g = ctx.createRadialGradient(end.x, end.y, 0, end.x, end.y, r);
        g.addColorStop(0, `rgba(235, 245, 255, ${0.9 * I})`);
        g.addColorStop(0.35, `rgba(90, 160, 255, ${0.5 * I})`);
        g.addColorStop(1, 'rgba(40, 110, 255, 0)');
        ctx.fillStyle = g;
        ctx.beginPath();
        ctx.arc(end.x, end.y, r, 0, Math.PI * 2);
        ctx.fill();
    }

    strokeLayers(pts, widthScale, intensity) {
        if (pts.length < 2 || intensity <= 0) return;
        const { ctx } = this;
        const path = new Path2D();
        path.moveTo(pts[0].x, pts[0].y);
        for (let i = 1; i < pts.length; i++) path.lineTo(pts[i].x, pts[i].y);
        ctx.lineCap = 'round';
        ctx.lineJoin = 'round';
        for (const [w, rgb, a] of LAYERS) {
            ctx.strokeStyle = `rgba(${rgb}, ${Math.min(1, a * intensity)})`;
            ctx.lineWidth = Math.max(0.6, w * widthScale);
            ctx.stroke(path);
        }
    }
}

/** The part of a polyline whose step index is <= progress (interpolating the last segment). */
function grow(pts, progress) {
    const out = [];
    for (let i = 0; i < pts.length; i++) {
        const p = pts[i];
        if (p.t <= progress) {
            out.push(p);
            continue;
        }
        const prev = pts[i - 1];
        if (prev && prev.t < progress) {
            const k = (progress - prev.t) / (p.t - prev.t);
            out.push({ x: prev.x + (p.x - prev.x) * k, y: prev.y + (p.y - prev.y) * k, t: progress });
        }
        break;
    }
    return out;
}
