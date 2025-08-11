

export const index = 10;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/dataviz/A2/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/10.81f26f8b.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.978c927b.js"];
export const stylesheets = [];
export const fonts = [];
