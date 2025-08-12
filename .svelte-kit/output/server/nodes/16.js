

export const index = 16;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/dataviz/A3/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/16.e5698f81.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.2a7a3823.js"];
export const stylesheets = [];
export const fonts = [];
