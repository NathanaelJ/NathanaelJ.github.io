import { c as create_ssr_component, e as escape } from "../../../../chunks/ssr.js";
import { b as base } from "../../../../chunks/paths.js";
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  const today = (/* @__PURE__ */ new Date()).toLocaleDateString();
  return `${$$result.head += `<!-- HEAD_svelte-1fyzf6q_START -->${$$result.title = `<title>Masters Thesis | N Jenkins</title>`, ""}<!-- HEAD_svelte-1fyzf6q_END -->`, ""} <main class="site-main"><div class="wrapper"><div class="page-header fade-in-up liquid-glass" data-svelte-h="svelte-1aef4ur"><h1>Masters Thesis</h1>  <p>For my masters&#39; thesis, I developed a physics-based model for the &#39;swept-stroke&#39; phase of lightning strikes on aircraft under the supervision of Prof. Guerra-Garcia in the <a href="apg.mit.edu">MIT Aerospace Plasma Group.</a> I am continuing the research for my <a href="${escape(base, true) + "/Projects/PhD"}">PhD</a>.<br><br></p> <a href="${escape(base, true) + "/Projects/FYPResources/NJenkins Thesis Final.pdf"}" class="project-link" download>Download PDF</a></div> <div class="pdf-container project-section fade-in-up liquid-glass" style="animation-delay: 0.4s;" data-svelte-h="svelte-fqy6gs"> <iframe class="pdf-viewer" title="Thesis" src="${escape(base, true) + "/Projects/FYPResources/NJenkins Thesis Final.pdf"}"></iframe> </div> <div class="citation-section fade-in-up liquid-glass" style="animation-delay: 0.8s;"><p data-svelte-h="svelte-hqa0fs">Please cite this project:</p> <p>Jenkins, N. (2023). <i data-svelte-h="svelte-e3xr31">Numerical Simulation of the Lightning Swept Stroke for
              the Zoning of Unconventional Aircraft.</i> [Master&#39;s Thesis.] Boston: Massachusetts Institute of Technology. Available at: http://nathanaelj.github.io/Projects/FYP [Accessed: ${escape(today)}]</p></div></div></main>`;
});
export {
  Page as default
};
