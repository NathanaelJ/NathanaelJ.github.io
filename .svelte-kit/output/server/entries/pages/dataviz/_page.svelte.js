import { c as create_ssr_component, d as each, v as validate_component } from "../../../chunks/ssr.js";
import { P as ProjectCard } from "../../../chunks/ProjectCard.js";
const vizProjects = [
  {
    title: "Boston Housing Data: Speculation",
    img: "/Thumbnails/DV_1.png",
    subtitle: "A2: Exploratory Visual Analysis",
    description: "Exploration of Boston housing data and the effect of speculation on house prices.",
    link: "dataviz/A2",
    year: "2025"
  },
  {
    title: "The COVID Spiral",
    img: "/Thumbnails/DV_2.png",
    subtitle: "A3: Visualization Critique and Redesign",
    description: "Critique and redesign of a widely-discussed COVID-19 visualization",
    link: "dataviz/A3",
    year: "2025"
  },
  {
    title: "Civilian Complaints to the NYPD",
    img: "/Thumbnails/DV_2.png",
    subtitle: "A4: Persuasive or Deceptive Visualization",
    description: "Using visualiaztions to draw opposite conclusions from the same data",
    link: "dataviz/A4",
    year: "2025"
  }
];
const _page_svelte_svelte_type_style_lang = "";
const css = {
  code: ".project-card.svelte-1winfil{background:var(--color-background);border-radius:8px;overflow:hidden;transition:transform 0.2s;box-shadow:0 2px 5px var(--color-border)}.project-card.svelte-1winfil:hover{transform:translateY(-5px)}",
  map: null
};
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  $$result.css.add(css);
  return `${$$result.head += `<!-- HEAD_svelte-keolbn_START -->${$$result.title = `<title>6.C85 Portfolio | N Jenkins</title>`, ""}<!-- HEAD_svelte-keolbn_END -->`, ""} <main class="site-main"><div class="wrapper"><h1 data-svelte-h="svelte-gz6v9k">6.C85: Interactive Data Visualisation and Society</h1> <p data-svelte-h="svelte-16bom1h">This portfolio contains my class work from an MIT class on data visualization and society.</p> <div class="projects-grid">${each(vizProjects, (p) => {
    return `${validate_component(ProjectCard, "ProjectCard").$$render($$result, { data: p }, {}, {})}`;
  })} <article class="project-card svelte-1winfil" data-svelte-h="svelte-g1nd31"><img src="/Thumbnails/PLACEHOLDER.jpeg" alt="Project thumbnail" class="project-image"> <div class="project-content"><h2>More coming soon...</h2></div></article></div></div> </main>`;
});
export {
  Page as default
};
