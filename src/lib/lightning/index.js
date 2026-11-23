// Small shared API so any page can call `strike(...)` and read/toggle storm mode.
import { writable } from 'svelte/store';

/** Storm mode: storm palette, random strikes, click-to-strike and thunder. */
export const storm = writable(false);

let engine = null;
let pending = [];

export function registerEngine(e) {
    engine = e;
    if (e) {
        pending.forEach(([target, opts]) => e.strike(target, opts));
    }
    pending = [];
}

/**
 * Strike an element (or a viewport point {x, y}).
 * @param {Element | {x: number, y: number}} target
 * @param {{ sound?: boolean, dim?: number }} [opts]
 */
export function strike(target, opts) {
    if (engine) return engine.strike(target, opts);
    pending.push([target, opts]);
}

export function strikeRandom(opts) {
    engine?.strikeRandom(opts);
}
