

export const index = 1;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/fallbacks/error.svelte.js')).default;
export const imports = ["_app/immutable/nodes/1.40ee460e.js","_app/immutable/chunks/scheduler.14a511a7.js","_app/immutable/chunks/index.2d17dc57.js","_app/immutable/chunks/stores.a5cbe0f5.js","_app/immutable/chunks/singletons.d4346ca1.js","_app/immutable/chunks/paths.f4401a76.js"];
export const stylesheets = [];
export const fonts = [];
