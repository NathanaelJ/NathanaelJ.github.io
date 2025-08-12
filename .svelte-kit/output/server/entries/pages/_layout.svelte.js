import { c as create_ssr_component, b as subscribe, e as escape, d as each } from "../../chunks/ssr.js";
import { b as base } from "../../chunks/paths.js";
import { p as page } from "../../chunks/stores.js";
import { p as projects } from "../../chunks/projects.js";
const Layout = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let routeId;
  let $page, $$unsubscribe_page;
  $$unsubscribe_page = subscribe(page, (value) => $page = value);
  routeId = $page?.route?.id || "";
  $$unsubscribe_page();
  return `${$$result.head += `<!-- HEAD_svelte-1bfhkmu_START --><style data-svelte-h="svelte-jkl6tf">@import url('https://fonts.googleapis.com/css2?family=Roboto+Serif:ital,opsz,wght@0,8..144,100..900;1,8..144,100..900&display=swap');</style><!-- HEAD_svelte-1bfhkmu_END -->`, ""} <header class="site-header"><div class="wrapper"><div class="title-block" data-svelte-h="svelte-1u8sz34"><a href="${escape(base, true) + "/."}" class="name">Nathanael Jenkins</a></div> <nav class="menu-right"><a href="${escape(base, true) + "/."}" class="${["menu-links", routeId === "/" ? "current-page" : ""].join(" ").trim()}" id="home-link" data-svelte-h="svelte-bk6eyb">Home</a> <div class="dropdown"><a class="${[
    "menu-links",
    routeId.includes("/Projects") || routeId.includes("dataviz") ? "current-page" : ""
  ].join(" ").trim()}" href="${escape(base, true) + "/Projects"}" id="projects-link" data-svelte-h="svelte-4vtyk9">Projects</a> <div class="dropdown-content"><div class="dropdown-label" data-svelte-h="svelte-wdb06u">Recommended</div> ${each(projects.filter((project) => project.dropdown), (project) => {
    return `<a href="${escape(base, true) + "/" + escape(project.link, true)}" id="${escape(project.title.toLowerCase().replace(/\s+/g, "-"), true) + "-link"}">${escape(project.button_title)}</a>`;
  })} <a href="${escape(base, true) + "/Projects"}" class="dropdown-view-all" data-svelte-h="svelte-tj4nqj">All Projects</a></div></div> <a href="${escape(base, true) + "/resume"}" class="${["menu-links", routeId.includes("/resume") ? "current-page" : ""].join(" ").trim()}" id="resume-link" data-svelte-h="svelte-v7ghps">Resume</a></nav></div> <hr class="rule"></header> ${slots.default ? slots.default({}) : ``} <footer class="footer" data-svelte-h="svelte-5j8b7x"><hr class="rule"> <nav class="social-links-container"><a class="social-links" href="https://www.linkedin.com/in/n-jenkins/" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/In.png" alt="LinkedIn"> LinkedIn</a> <a class="social-links" href="https://github.com/NathanaelJ" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/Git.png" alt="GitHub"> GitHub</a></nav> <div class="footer-right"><p>© Nathanael Jenkins, 2025</p> <p>improved using <a href="https://cursor.com/" target="_blank" rel="noreferrer noopener">Cursor</a></p></div></footer>`;
});
export {
  Layout as default
};
