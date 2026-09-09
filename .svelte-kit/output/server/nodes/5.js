

export const index = 5;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/Projects/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/5.7b14653b.js","_app/immutable/chunks/scheduler.14a511a7.js","_app/immutable/chunks/index.2d17dc57.js","_app/immutable/chunks/each.e59479a4.js","_app/immutable/chunks/projects.8fc24596.js","_app/immutable/chunks/ProjectCard.b787c18c.js","_app/immutable/chunks/paths.f4401a76.js"];
export const stylesheets = [];
export const fonts = [];
