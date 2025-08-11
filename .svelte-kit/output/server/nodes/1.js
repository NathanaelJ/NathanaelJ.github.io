

export const index = 1;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/fallbacks/error.svelte.js')).default;
export const imports = ["_app/immutable/nodes/1.2858928a.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.978c927b.js","_app/immutable/chunks/stores.00b59846.js","_app/immutable/chunks/singletons.848f5067.js","_app/immutable/chunks/paths.d4eddcfa.js"];
export const stylesheets = [];
export const fonts = [];
