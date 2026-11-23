import { loadTravels } from '$lib/server/travels.js';

// Runs at build time (every page is prerendered via src/routes/+layout.js), so only the
// airports actually flown are sent to the page — the full airport table never reaches visitors.

export function load() {
    return loadTravels();
}
