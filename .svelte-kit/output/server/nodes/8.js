

export const index = 8;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/Projects/Thesis/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/8.20ae909d.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.978c927b.js"];
export const stylesheets = [];
export const fonts = [];
