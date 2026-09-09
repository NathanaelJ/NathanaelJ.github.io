

export const index = 4;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/CV/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/4.91c69eca.js","_app/immutable/chunks/scheduler.14a511a7.js","_app/immutable/chunks/index.2d17dc57.js","_app/immutable/chunks/paths.f4401a76.js"];
export const stylesheets = [];
export const fonts = [];
