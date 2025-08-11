import { c as create_ssr_component, e as escape } from "../../chunks/ssr.js";
import { b as base } from "../../chunks/paths.js";
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  return `${$$result.head += `<!-- HEAD_svelte-n7m23f_START -->${$$result.title = `<title>Nathanael Jenkins</title>`, ""}<!-- HEAD_svelte-n7m23f_END -->`, ""} <main class="site-main" data-svelte-h="svelte-kpo44l"><div class="intro-container"><img src="/resources-General/Self.jpg" class="introimg" alt="Nathanael Jenkins portrait"> <div class="intro-text"><h1>Hi there!</h1> <p>I&#39;m Nathanael, a PhD student in Aeronautics and Astronautics at the <a href="https://www.mit.edu" target="_blank" rel="noreferrer noopener">Massachusetts Institute of Technology</a>. Welcome to my little space on the web.</p></div></div> <div class="intro-container"><div class="intro-text"><p>I specialize in physics simulations and my current research explores simulation tools for aircraft lightning protection. You can find out more about my projects <a href="${escape(base, true) + "/Projects"}">here</a>.</p></div> <figure><img src="/resources-General/CFD_Dark.gif" class="introimg" alt="Animated Taylor-Green vortex"> <figcaption>DNS of a Taylor-Green vortex using <a href="https://www.incompact3d.com" target="_blank" rel="noreferrer noopener">Incompact3D</a></figcaption></figure></div> <br></main>`;
});
export {
  Page as default
};
