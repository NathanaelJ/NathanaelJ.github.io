<script>
    import { onMount } from 'svelte';
    import { geoAlbersUsa, geoEqualEarth, geoPath } from 'd3';
    import { feature } from 'topojson-client';
    import { dropAntarctica, featureId, featureName, flightPath } from '$lib/travels/geo.js';

    export let kind = 'world'; // 'world' | 'us'
    export let topoUrl;
    export let visited = [];
    export let routes = [];
    export let airports = {};
    export let count = 0;
    export let total = 0;
    export let unit = 'countries';

    const WIDTH = 960;
    let viewBox = kind === 'world' ? `0 0 ${WIDTH} 420` : `0 0 ${WIDTH} 600`;
    let shapes = [];
    let flights = [];
    let dots = [];
    let ready = false;
    let inView = false;

    // Screen px -> SVG user units, so lines stay hairline-thin at any screen width
    let u = 1;
    let svgEl;

    let active = null; // hovered/tapped flight route
    let place = null; // hovered/tapped country or state
    let tip = { x: 0, y: 0 };

    function build(topo) {
        const visitedSet = new Set(visited);
        let features;
        let projection;
        if (kind === 'world') {
            features = dropAntarctica(feature(topo, topo.objects.countries).features, visitedSet);
            projection = geoEqualEarth();
        } else {
            // 50 states + DC (drops territories that the Albers USA projection can't place)
            features = feature(topo, topo.objects.states).features.filter((f) => +f.id <= 56);
            projection = geoAlbersUsa();
        }
        const collection = { type: 'FeatureCollection', features };
        projection.fitWidth(WIDTH, collection);
        const path = geoPath(projection);

        const [[x0, y0], [x1, y1]] = path.bounds(collection);
        viewBox = [x0 - 2, y0 - 2, x1 - x0 + 4, y1 - y0 + 4].map(Math.round).join(' ');

        shapes = features
            .map((f) => ({ name: featureName(f), d: path(f), visited: visitedSet.has(featureId(f)) }))
            .filter((s) => s.d)
            // visited shapes last, so their outlines sit on top of their neighbours'
            .sort((a, b) => a.visited - b.visited);

        const used = new Set();
        flights = routes
            .map((r) => {
                const A = airports[r.a];
                const B = airports[r.b];
                const d = flightPath(projection, [A.lon, A.lat], [B.lon, B.lat]);
                if (d) used.add(r.a).add(r.b);
                return d && { ...r, d, key: `${r.a}-${r.b}` };
            })
            .filter(Boolean);

        dots = [...used].map((code) => projection([airports[code].lon, airports[code].lat]));
    }

    function updateScale() {
        if (!svgEl) return;
        const vbWidth = +viewBox.split(' ')[2];
        const px = svgEl.getBoundingClientRect().width;
        if (px) u = vbWidth / px;
    }

    function show(route, e) {
        active = route;
        place = null;
        moveTip(e);
    }

    function showPlace(shape, e) {
        place = shape;
        active = null;
        moveTip(e);
    }

    function moveTip(e) {
        const pad = 14;
        const w = 220;
        const x = e.clientX + pad + w > window.innerWidth ? e.clientX - pad - w : e.clientX + pad;
        tip = { x: Math.max(8, x), y: e.clientY + pad };
    }

    function onEnter(route, e) {
        if (e.pointerType === 'mouse') show(route, e);
    }

    function onLeave(e) {
        if (e.pointerType === 'mouse') active = null;
    }

    function onPlaceEnter(shape, e) {
        if (e.pointerType === 'mouse') showPlace(shape, e);
    }

    function onPlaceLeave(e) {
        if (e.pointerType === 'mouse') place = null;
    }

    function onPlaceTap(shape, e) {
        e.stopPropagation();
        if (lastPointer !== 'mouse') place === shape ? (place = null) : showPlace(shape, e);
    }

    // Touch/pen: tap a route to show it, tap anywhere else to dismiss.
    // (Some browsers don't set pointerType on click events, so remember it from pointerdown.)
    let lastPointer = 'mouse';
    function onTap(route, e) {
        e.stopPropagation();
        if (lastPointer !== 'mouse') active === route ? (active = null) : show(route, e);
    }

    onMount(() => {
        let cancelled = false;
        fetch(topoUrl)
            .then((r) => r.json())
            .then((topo) => {
                if (cancelled) return;
                build(topo);
                ready = true;
                requestAnimationFrame(updateScale);
            });

        const ro = new ResizeObserver(updateScale);
        ro.observe(svgEl);

        const io = new IntersectionObserver(
            ([entry]) => {
                if (entry.isIntersecting) {
                    inView = true;
                    io.disconnect();
                }
            },
            { threshold: 0.25 }
        );
        io.observe(svgEl);

        const dismiss = () => {
            active = null;
            place = null;
        };
        window.addEventListener('click', dismiss);
        window.addEventListener('scroll', dismiss, { passive: true });

        return () => {
            cancelled = true;
            ro.disconnect();
            io.disconnect();
            window.removeEventListener('click', dismiss);
            window.removeEventListener('scroll', dismiss);
        };
    });

    $: viewBox, updateScale();
    $: city = (code) => airports[code]?.city ?? '';
</script>

<figure class="travel-map" class:ready class:drawn={ready && inView}>
    <svg
        bind:this={svgEl}
        {viewBox}
        role="img"
        aria-label="Map of {unit} visited: {count} of {total}"
        style="--u: {u}"
    >
        <g class="shapes">
            <!-- not keyed: a few countries are split into several shapes that share an ISO id -->
            {#each shapes as s}
                <path
                    d={s.d}
                    class:visited={s.visited}
                    class:hovered={place === s}
                    on:pointerenter={(e) => onPlaceEnter(s, e)}
                    on:pointermove={(e) => e.pointerType === 'mouse' && moveTip(e)}
                    on:pointerleave={onPlaceLeave}
                    on:pointerdown={(e) => (lastPointer = e.pointerType)}
                    on:click={(e) => onPlaceTap(s, e)}
                />
            {/each}
        </g>
        <g class="flights" class:has-active={active}>
            {#each flights as f, i (f.key)}
                <path
                    class="flight"
                    class:active={active === f}
                    d={f.d}
                    pathLength="1"
                    style="--delay: {i * 120}ms"
                />
            {/each}
            {#each dots as [x, y]}
                <circle class="airport" cx={x} cy={y} r={2.2 * u} />
            {/each}
            {#each flights as f (f.key)}
                <path
                    class="hit"
                    d={f.d}
                    on:pointerenter={(e) => onEnter(f, e)}
                    on:pointermove={(e) => e.pointerType === 'mouse' && moveTip(e)}
                    on:pointerleave={onLeave}
                    on:pointerdown={(e) => (lastPointer = e.pointerType)}
                    on:click={(e) => onTap(f, e)}
                />
            {/each}
        </g>
    </svg>
    <figcaption class="travel-count"><span>{count}</span> / {total} {unit}</figcaption>
</figure>

{#if active}
    <div class="flight-tip" style="left: {tip.x}px; top: {tip.y}px" role="tooltip">
        <div class="tip-route">{active.a} ⇄ {active.b}</div>
        <div class="tip-cities">{city(active.a)} · {city(active.b)}</div>
        {#if active.ab}
            <div class="tip-row"><span>{active.a} → {active.b}</span><span>{active.ab}×</span></div>
        {/if}
        {#if active.ba}
            <div class="tip-row"><span>{active.b} → {active.a}</span><span>{active.ba}×</span></div>
        {/if}
    </div>
{:else if place}
    <div class="flight-tip" style="left: {tip.x}px; top: {tip.y}px" role="tooltip">
        <div class="tip-place">{place.name}</div>
    </div>
{/if}

<style>
    .travel-map {
        margin: 0 0 var(--spacing-16);
        padding: 0;
    }

    svg {
        display: block;
        width: 100%;
        height: auto;
        overflow: visible;
        opacity: 0;
        transition: opacity 0.6s ease;
    }

    .ready svg {
        opacity: 1;
    }

    .shapes path {
        fill: none;
        stroke: var(--color-map-outline);
        stroke-width: 0.6px;
        stroke-linejoin: round;
        vector-effect: non-scaling-stroke;
    }

    .shapes path {
        pointer-events: all;
        transition: fill 0.15s ease;
    }

    .shapes path.visited {
        fill: var(--color-bronze);
        stroke: var(--color-bronze-dark);
    }

    .shapes path.hovered {
        fill: var(--color-surface);
    }

    .shapes path.visited.hovered {
        fill: var(--color-bronze-dark);
    }

    .flight {
        fill: none;
        stroke: var(--color-text-primary);
        stroke-width: calc(1.1 * var(--u));
        stroke-linecap: round;
        stroke-opacity: 0.7;
        stroke-dasharray: 1;
        stroke-dashoffset: 1;
        transition:
            stroke-dashoffset 1.4s cubic-bezier(0.45, 0, 0.2, 1) var(--delay, 0ms),
            stroke 0.2s ease,
            stroke-opacity 0.2s ease;
    }

    .drawn .flight {
        stroke-dashoffset: 0;
    }

    .has-active .flight {
        stroke-opacity: 0.18;
    }

    .flights .flight.active {
        stroke: var(--color-bronze-dark);
        stroke-opacity: 1;
        stroke-width: calc(2.2 * var(--u));
    }

    .airport {
        fill: var(--color-text-primary);
        opacity: 0;
        transition: opacity 0.6s ease 1.2s;
    }

    .drawn .airport {
        opacity: 0.8;
    }

    .hit {
        fill: none;
        stroke: transparent;
        stroke-width: calc(14 * var(--u));
        pointer-events: stroke;
        cursor: pointer;
    }

    .travel-count {
        margin-top: var(--spacing-4);
        font-family: var(--font-primary);
        font-size: 0.78rem;
        font-style: normal;
        font-weight: 500;
        letter-spacing: 0.12em;
        text-transform: uppercase;
        color: var(--color-text-light);
        text-align: center;
    }

    .travel-count span {
        font-family: var(--font-serif);
        font-size: 1.4rem;
        font-weight: 600;
        letter-spacing: 0;
        color: var(--color-bronze-dark);
        margin-right: 0.15em;
    }

    .flight-tip {
        position: fixed;
        z-index: 200;
        width: max-content;
        max-width: 220px;
        pointer-events: none;
        background: var(--color-text-primary);
        color: var(--color-background);
        padding: var(--spacing-2) var(--spacing-3);
        font-size: 0.8rem;
        line-height: 1.45;
        box-shadow: 0 6px 18px rgba(24, 32, 25, 0.18);
    }

    .tip-route {
        font-family: var(--font-serif);
        font-weight: 600;
        font-size: 0.95rem;
        letter-spacing: 0.02em;
    }

    .tip-place {
        font-family: var(--font-serif);
        font-weight: 600;
        font-size: 0.9rem;
    }

    .tip-cities {
        opacity: 0.7;
        margin-bottom: var(--spacing-1);
    }

    .tip-row {
        display: flex;
        justify-content: space-between;
        gap: var(--spacing-4);
        font-variant-numeric: tabular-nums;
    }

    @media (prefers-reduced-motion: reduce) {
        svg,
        .flight,
        .airport {
            transition: none;
        }
    }
</style>
