import { c as create_ssr_component, d as each, v as validate_component } from "../../../chunks/ssr.js";
import { p as projects } from "../../../chunks/projects.js";
import { P as ProjectCard } from "../../../chunks/ProjectCard.js";
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let filteredByYear;
  filteredByYear = projects;
  return `${$$result.head += `<!-- HEAD_svelte-1lo32wf_START -->${$$result.title = `<title>Projects | N Jenkins</title>`, ""}<!-- HEAD_svelte-1lo32wf_END -->`, ""} <main class="site-main"><div class="wrapper"><div class="page-header fade-in-up" data-svelte-h="svelte-1ptd719"><h1>Portfolio</h1> <p>Explore my recent projects and research work.</p></div> <div class="projects-grid">${each(filteredByYear, (p) => {
    return `${validate_component(ProjectCard, "ProjectCard").$$render($$result, { data: p }, {}, {})}`;
  })}</div></div></main>`;
});
export {
  Page as default
};
