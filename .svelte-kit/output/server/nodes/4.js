

export const index = 4;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/Projects/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/4.b1436fe5.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.2a7a3823.js","_app/immutable/chunks/each.e59479a4.js","_app/immutable/chunks/projects.2ea50a94.js","_app/immutable/chunks/ProjectCard.522ed22f.js","_app/immutable/chunks/paths.58b3601a.js"];
export const stylesheets = [];
export const fonts = [];
