import { c as create_ssr_component, d as each, e as escape, v as validate_component } from "../../../../chunks/ssr.js";
import { b as base } from "../../../../chunks/paths.js";
import { P as ProjectCard } from "../../../../chunks/ProjectCard.js";
const pubs = [
  {
    title: "A Physics-Based Approach to Aircraft Lightning Zoning: Zone 2",
    button_title: "A Physics-Based Approach to Aircraft Lightning Zoning: Zone 2",
    year: "2025",
    img: "/Projects/PhDResources/Thumbnails/IEEE_Z2.png",
    subtitle: "IEEE Access, Vol 13",
    description: "A Physics-Based Approach to Aircraft Lightning Zoning: Zone 2",
    link: "external:https://doi.org/10.1109/ACCESS.2025.3628197",
    dropdown: false
  },
  {
    title: "Physical Interpretation of Swept Stroke Data",
    button_title: "Physical Interpretation of Swept Stroke Data",
    year: "2025",
    img: "/Projects/PhDResources/Thumbnails/Suppl.png",
    subtitle: "Supplementary to 'A Physics-Based Approach to Aircraft Lightning Zoning: Zone 2'",
    description: "Physical Interpretation of Swept Stroke Data (Supplementary Document)",
    link: "external:https://nathanaelj.github.io/Projects/PhDResources/IEEE_Suppl.pdf",
    dropdown: false
  },
  {
    title: "Numerical Simulation of the Lightning Swept Stroke: Application to the Results from the NASA Storm Hazards Program",
    button_title: "Numerical Simulation of the Lightning Swept Stroke",
    year: "2024",
    img: "/Projects/PhDResources/Thumbnails/IEEE_SHP.png",
    subtitle: "IEEE Access, Vol 12",
    description: "Numerical Simulation of the Lightning Swept Stroke: Application to the Results from the NASA Storm Hazards Program.",
    link: "external:https://doi.org/10.1109/ACCESS.2024.3515833",
    dropdown: false
  },
  {
    title: "Physics-Based Zoning of Unconventional Aircraft: The Swept Stroke Phase (Zenodo)",
    button_title: "Physics-Based Zoning (Zenodo)",
    year: "2024",
    img: "/Projects/PhDResources/Thumbnails/ICOLSE.png",
    subtitle: "International Conference On Lightning and Static Electricity (ICOLSE), Brazil.",
    description: "Physics-Based Zoning of Unconventional Aircraft: The Swept Stroke Phase.",
    link: "external:https://zenodo.org/records/13838314",
    dropdown: false
  }
];
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let filteredByYear;
  (/* @__PURE__ */ new Date()).toLocaleDateString();
  filteredByYear = pubs;
  return `${$$result.head += `<!-- HEAD_svelte-1dh6126_START -->${$$result.title = `<title>PhD Research | N Jenkins</title>`, ""}<!-- HEAD_svelte-1dh6126_END -->`, ""} <main class="site-main"><div class="wrapper"><div class="page-header  " data-svelte-h="svelte-fku2os"><h1>PhD Research</h1> <p>On average, an aircraft is struck by lightning somewhere in the world every 20 minutes. This project is working towards an improved understanding of aircraft-lightning physics, and the development of reliable engineering methods for protecting aircraft of the future from lightning hazards.<br></p> <a href="https://news.mit.edu/2025/lightning-prediction-tool-could-help-protect-planes-future-1104" class="project-link" target="_blank" rel="noreferrer noopener">Check out our feature in MIT News ⇱</a></div> <div class="project-section" data-svelte-h="svelte-1n5cwly"><h3>Publications</h3></div> <div class="projects-grid">${each(filteredByYear, (p) => {
    return `${validate_component(ProjectCard, "ProjectCard").$$render($$result, { data: p }, {}, {})}`;
  })}</div>   <div class="project-section  " style="animation-delay: 0.8s;" data-svelte-h="svelte-1wb5v51"><h3>Related Links</h3> <div class="download-buttons"><a href="${escape(base, true) + "/Projects/Thesis"}" target="_blank" rel="noreferrer noopener" class="download-btn ">Masters Thesis</a> <a href="https://apg.mit.edu" target="_blank" rel="noreferrer noopener" class="download-btn ">⇱ Aerospace Plasma Group</a> <a href="https://aeroastro.mit.edu/people/carmen-guerra-garcia/" target="_blank" rel="noreferrer noopener" class="download-btn ">⇱ Prof. Guerra-Garcia</a></div></div>  </div></main>`;
});
export {
  Page as default
};
