

export const index = 0;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/_layout.svelte.js')).default;
export const imports = ["_app/immutable/nodes/0.fdd9aa31.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.978c927b.js","_app/immutable/chunks/paths.d4eddcfa.js","_app/immutable/chunks/stores.00b59846.js","_app/immutable/chunks/singletons.848f5067.js"];
export const stylesheets = ["_app/immutable/assets/0.08ec65af.css"];
export const fonts = [];
