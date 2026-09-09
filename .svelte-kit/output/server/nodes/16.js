

export const index = 16;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/dataviz/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/16.6ebe6254.js","_app/immutable/chunks/scheduler.14a511a7.js","_app/immutable/chunks/index.2d17dc57.js","_app/immutable/chunks/each.e59479a4.js","_app/immutable/chunks/ProjectCard.b787c18c.js","_app/immutable/chunks/paths.f4401a76.js"];
export const stylesheets = [];
export const fonts = [];
