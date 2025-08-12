

export const index = 9;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/Projects/Aircraft/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/9.77a7d126.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.2a7a3823.js","_app/immutable/chunks/each.e59479a4.js","_app/immutable/chunks/MissileModel.267338f4.js"];
export const stylesheets = [];
export const fonts = [];
