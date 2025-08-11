import { c as create_ssr_component, e as escape, d as each, v as validate_component } from "../../../chunks/ssr.js";
import { P as ProjectCard } from "../../../chunks/ProjectCard.js";
const projects = [
  {
    title: "Data Visualizations",
    year: "2024",
    img: "/Thumbnails/DV_1.png",
    subtitle: "6.C85: Interactive Data Visualisation and Society",
    description: "MIT class work using interactive data visualization to analyse the Boston housing market.",
    link: "dataviz"
  },
  {
    title: "Masters' Thesis",
    year: "2024",
    img: "/Thumbnails/FYP.png",
    subtitle: "Numerical modelling of the lightning swept stroke",
    description: "Development of a physics-based simulation tool for aircraft lightning zoning.",
    link: "Projects/Thesis"
  },
  {
    title: "CAD Models",
    year: "2023",
    img: "/Thumbnails/Modelling.png",
    subtitle: "Missile and aircraft models",
    description: "Sizing and modelling of various missiles and aircraft.",
    link: "Projects/Modelling"
  },
  {
    title: "ICL Rocketry",
    year: "2023",
    img: "/Thumbnails/ASTRA.png",
    subtitle: "Altitude Record Team",
    description: "Contributions to ICLR reacord-breaking attempts as Aerodynamics and Simulations team lead.",
    link: "Projects/ICLR"
  },
  {
    title: "Academic Projects",
    year: "2022",
    img: "/Thumbnails/GDP.png",
    subtitle: "Undergraduate and high school projects",
    description: "A collection of fun projects from my studies",
    link: "Projects/Academic"
  }
];
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let filteredByYear;
  filteredByYear = projects;
  return `${$$result.head += `<!-- HEAD_svelte-1lo32wf_START -->${$$result.title = `<title>Projects | N Jenkins</title>`, ""}<!-- HEAD_svelte-1lo32wf_END -->`, ""} <main class="site-main"><div class="wrapper"><h1>${escape(projects.length)} Projects</h1> <p data-svelte-h="svelte-n0hn0u">Explore my recent projects.</p> <div class="projects-grid">${each(filteredByYear, (p) => {
    return ` ${validate_component(ProjectCard, "ProjectCard").$$render($$result, { data: p }, {}, {})}`;
  })}</div></div></main>`;
});
export {
  Page as default
};
