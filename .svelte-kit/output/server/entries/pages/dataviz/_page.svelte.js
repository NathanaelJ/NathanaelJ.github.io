import { c as create_ssr_component, d as each, v as validate_component } from "../../../chunks/ssr.js";
import { P as ProjectCard } from "../../../chunks/ProjectCard.js";
const vizProjects = [
  {
    title: "Hollowvale",
    img: "/Thumbnails/Hollowvale.png",
    subtitle: "Final Project: Visualizing Speculation in Boston Housing Markets",
    description: "A group project creating a tool for policymakers to understand the impact of speculation on specific municipailities in Greater Boston",
    link: "external:https://hollowvale.vercel.app",
    year: "2025"
  },
  {
    title: "Civilian Complaints to the NYPD",
    img: "/Thumbnails/DV_3.png",
    subtitle: "A4: Persuasive or Deceptive Visualization",
    description: "Using visualiaztions to draw opposite conclusions from the same data",
    link: "dataviz/A4",
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
    title: "Speculation in Boston",
    img: "/Thumbnails/DV_1.png",
    subtitle: "A2: Exploratory Visual Analysis",
    description: "Exploration of Boston housing data and the effect of speculation on house prices.",
    link: "dataviz/A2",
    year: "2025"
  }
];
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  return `${$$result.head += `<!-- HEAD_svelte-keolbn_START -->${$$result.title = `<title>6.C85 Portfolio | N Jenkins</title>`, ""}<!-- HEAD_svelte-keolbn_END -->`, ""} <main class="site-main"><div class="wrapper"><div class="page-header fade-in-up" data-svelte-h="svelte-1wbncva"><h1>6.C85: Interactive Data Visualisation and Society</h1> <p>This contains my class work from the MIT class on <a href="https://vis-society.github.io/final-project/showcase/" target="_blank" rel="noopener">interactive data visualization and society</a> (Fall 2024).</p></div> <div class="projects-grid">${each(vizProjects, (p) => {
    return `${validate_component(ProjectCard, "ProjectCard").$$render($$result, { data: p }, {}, {})}`;
  })}</div></div></main>`;
});
export {
  Page as default
};
