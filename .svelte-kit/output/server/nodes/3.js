

export const index = 3;
let component_cache;
export const component = async () => component_cache ??= (await import('../entries/pages/404/_page.svelte.js')).default;
export const imports = ["_app/immutable/nodes/3.4929e3f4.js","_app/immutable/chunks/scheduler.63274e7e.js","_app/immutable/chunks/index.2a7a3823.js","_app/immutable/chunks/paths.58b3601a.js"];
export const stylesheets = [];
export const fonts = [];
