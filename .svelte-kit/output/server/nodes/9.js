

export const index = 9;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/dataviz/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/9.b5f5a418.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.978c927b.js","_app/immutable/chunks/ProjectCard.cbe5b2a4.js","_app/immutable/chunks/paths.d4eddcfa.js"];
export const stylesheets = ["_app/immutable/assets/9.cf1e1a1c.css"];
export const fonts = [];
