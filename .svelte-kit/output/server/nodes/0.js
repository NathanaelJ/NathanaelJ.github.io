

export const index = 0;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/_layout.svelte.js')).default;
export const imports = ["_app/immutable/nodes/0.0a227a41.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.2a7a3823.js","_app/immutable/chunks/each.e59479a4.js","_app/immutable/chunks/paths.58b3601a.js","_app/immutable/chunks/stores.3f3c5887.js","_app/immutable/chunks/singletons.52006076.js","_app/immutable/chunks/projects.2ea50a94.js"];
export const stylesheets = [];
export const fonts = [];
