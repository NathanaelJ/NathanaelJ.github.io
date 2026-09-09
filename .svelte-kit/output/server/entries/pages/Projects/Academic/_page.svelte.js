import { c as create_ssr_component, d as each, v as validate_component } from "../../../../chunks/ssr.js";
import { P as ProjectCard } from "../../../../chunks/ProjectCard.js";
import { p as projects } from "../../../../chunks/projects.js";
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let academicProjects;
  academicProjects = projects.filter((project) => project.link.includes("/Academic/"));
  return `${$$result.head += `<!-- HEAD_svelte-o9luxi_START -->${$$result.title = `<title>Academic Projects | N Jenkins</title>`, ""}<!-- HEAD_svelte-o9luxi_END -->`, ""} <main class="site-main"><div class="wrapper"><div class="page-header fade-in-up" data-svelte-h="svelte-1iq70so"><h1>Academic Projects</h1> <p>A collection of projects from my undergraduate and pre-university studies</p></div> <div class="projects-grid">${each(academicProjects, (project) => {
    return `${validate_component(ProjectCard, "ProjectCard").$$render($$result, { data: project }, {}, {})}`;
  })}</div></div></main>`;
});
export {
  Page as default
};
