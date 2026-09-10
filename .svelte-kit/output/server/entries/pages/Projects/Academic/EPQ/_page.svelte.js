import { c as create_ssr_component, e as escape } from "../../../../../chunks/ssr.js";
import { b as base } from "../../../../../chunks/paths.js";
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  const today = (/* @__PURE__ */ new Date()).toLocaleDateString();
  return `${$$result.head += `<!-- HEAD_svelte-bq9pf0_START -->${$$result.title = `<title>Ion Propulsion - Extended Project Qualification | N Jenkins</title>`, ""}<!-- HEAD_svelte-bq9pf0_END -->`, ""} <main class="site-main"><div class="wrapper"><div class="page-header  "><h1 data-svelte-h="svelte-1d2nx3j">Ion Propulsion</h1> <p data-svelte-h="svelte-1u39uly">Alongside A-Level studies, I conducted an &#39;Extended Project Qualification&#39; (EPQ) exploring ion propulsion for air and space travel.<br></p> <div class="citation-section  " style="animation-delay: 0.8s;"><p data-svelte-h="svelte-hqa0fs">Please cite this project:</p> <p>Jenkins, N. (2019). <i data-svelte-h="svelte-1n5j14p">Is ion propulsion the future of air and space transport?</i> [pdf] Winchester: Peter Symonds College. Available at: http://nathanaelj.github.io/Projects/AcademicResources/EPQ.pdf [Accessed: ${escape(today)}]</p></div> <a href="${escape(base, true) + "/Projects/AcademicResources/EPQ.pdf"}" class="project-link" download data-svelte-h="svelte-1eavlzd">Download PDF</a></div> <div class="pdf-container" data-svelte-h="svelte-s9v08w"><iframe class="pdf-viewer" title="Extended Project Report" src="${escape(base, true) + "/Projects/AcademicResources/EPQ.pdf"}"></iframe></div></div></main>`;
});
export {
  Page as default
};
