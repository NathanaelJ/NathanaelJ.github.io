<script>
    import { onMount } from 'svelte';
    import { get } from 'svelte/store';
    import { LightningEngine } from '$lib/lightning/engine.js';
    import { registerEngine, storm } from '$lib/lightning/index.js';

    let canvas;

    // Clicking these should do their normal job, not summon lightning
    const INTERACTIVE = 'a, button, input, textarea, select, label, summary, video, iframe, svg, [role="button"], .strikeable';

    onMount(() => {
        const engine = new LightningEngine(canvas);
        registerEngine(engine);

        let timer;
        const schedule = () => {
            timer = setTimeout(() => {
                if (!document.hidden) engine.strikeRandom({ sound: true, dim: 0.25 });
                schedule();
            }, 5000 + Math.random() * 7000);
        };

        // Storm mode deliberately isn't saved: every fresh load or refresh starts calm
        const unsubscribe = storm.subscribe((on) => {
            document.documentElement.classList.toggle('storm', on);
            clearTimeout(timer);
            if (on) schedule();
        });

        // In storm mode, clicking/tapping empty space calls down a strike there
        const onClick = (e) => {
            if (!get(storm) || e.defaultPrevented) return;
            if (e.target instanceof Element && e.target.closest(INTERACTIVE)) return;
            if (window.getSelection && !window.getSelection().isCollapsed) return;
            engine.strike({ x: e.clientX, y: e.clientY }, { sound: true });
        };

        window.addEventListener('click', onClick);

        return () => {
            clearTimeout(timer);
            unsubscribe();
            window.removeEventListener('click', onClick);
            registerEngine(null);
            engine.destroy();
        };
    });
</script>

<canvas bind:this={canvas} class="lightning-canvas" aria-hidden="true"></canvas>

<style>
    .lightning-canvas {
        position: fixed;
        inset: 0;
        width: 100%;
        height: 100%;
        pointer-events: none;
        z-index: 150;
    }
</style>
