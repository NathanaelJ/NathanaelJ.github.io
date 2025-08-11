

export const index = 6;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/Projects/ICLR/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/6.8e7a1570.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.978c927b.js"];
export const stylesheets = [];
export const fonts = [];
