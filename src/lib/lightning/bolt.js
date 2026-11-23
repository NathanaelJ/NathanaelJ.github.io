// Lightning geometry, loosely modelled on a stepped leader: the channel advances in short,
// randomly-angled steps biased towards the attachment point, spawning branches that die out.
// Each step is then roughened with midpoint displacement, so the channel has fine-scale
// tortuosity rather than straight polygon edges. Every point carries a (fractional) step
// index `t`, so the leader can be "grown" over time.

/**
 * @param {{ from: [number, number], to: [number, number], step: number, rand?: () => number }} opts
 * @returns {{ main: {x:number,y:number,t:number}[], branches: {pts:{x:number,y:number,t:number}[], depth:number}[], length: number }}
 */
export function makeBolt({ from, to, step, rand = Math.random }) {
    const [x1, y1] = to;
    let [x, y] = from;
    const main = [{ x, y, t: 0 }];
    const branches = [];
    const maxSteps = Math.ceil((Math.hypot(x1 - x, y1 - y) / step) * 3) + 10;

    let i = 0;
    while (i < maxSteps) {
        const dx = x1 - x;
        const dy = y1 - y;
        const dist = Math.hypot(dx, dy);
        if (dist < step * 1.2) break;

        // Wander far from the target, home in when close
        const wander = dist > step * 4 ? 1.05 : 0.4;
        const angle = Math.atan2(dy, dx) + (rand() - 0.5) * wander;
        const len = step * (0.6 + rand() * 0.7);
        x += Math.cos(angle) * len;
        y += Math.sin(angle) * len;
        i++;
        main.push({ x, y, t: i });

        if (dist > step * 5 && rand() < 0.22) {
            branches.push(...growBranch(x, y, angle, i, step, 1, rand));
        }
    }
    main.push({ x: x1, y: y1, t: i + 1 });

    return {
        main: roughen(main, 3, rand),
        branches: branches.map((b) => ({ ...b, pts: roughen(b.pts, b.depth === 1 ? 2 : 1, rand) })),
        length: i + 1
    };
}

function growBranch(x, y, parentAngle, t0, step, depth, rand) {
    const side = rand() < 0.5 ? -1 : 1;
    const heading = parentAngle + side * (0.35 + rand() * 0.6);
    const steps = Math.floor(depth === 1 ? 4 + rand() * 12 : 2 + rand() * 6);
    const pts = [{ x, y, t: t0 }];
    const out = [{ pts, depth }];

    let s = step * 0.85;
    for (let k = 1; k <= steps; k++) {
        const a = heading + (rand() - 0.5) * 0.9;
        const len = s * (0.55 + rand() * 0.6);
        x += Math.cos(a) * len;
        y += Math.sin(a) * len;
        pts.push({ x, y, t: t0 + k });
        s *= 0.94;
        if (depth < 3 && rand() < 0.12 / depth) {
            out.push(...growBranch(x, y, a, t0 + k, s, depth + 1, rand));
        }
    }
    return out;
}

/**
 * Midpoint displacement: split every segment in two and nudge the midpoint sideways by a
 * random fraction of the segment length, `levels` times. Endpoints never move.
 */
function roughen(pts, levels, rand, amount = 0.22) {
    let out = pts;
    for (let level = 0; level < levels; level++) {
        const next = [out[0]];
        for (let i = 1; i < out.length; i++) {
            const a = out[i - 1];
            const b = out[i];
            const dx = b.x - a.x;
            const dy = b.y - a.y;
            const offset = (rand() - 0.5) * 2 * amount; // fraction of segment length, along the normal
            next.push({ x: (a.x + b.x) / 2 - dy * offset, y: (a.y + b.y) / 2 + dx * offset, t: (a.t + b.t) / 2 }, b);
        }
        out = next;
    }
    return out;
}
