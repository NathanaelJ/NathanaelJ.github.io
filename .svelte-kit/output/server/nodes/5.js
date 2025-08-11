

export const index = 5;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/Projects/Academic/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/5.490c7dc4.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.978c927b.js"];
export const stylesheets = [];
export const fonts = [];
