import { c as create_ssr_component } from "../../chunks/ssr.js";
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  return `${$$result.head += `<!-- HEAD_svelte-n7m23f_START -->${$$result.title = `<title>Nathanael Jenkins</title>`, ""}<!-- HEAD_svelte-n7m23f_END -->`, ""} <main class="site-main" data-svelte-h="svelte-dzducn"><div class="intro-container " style="margin-top: 0;"><img src="/resources-General/Self.jpg" class="introimg" alt="Nathanael Jenkins portrait"> <div class="intro-text"><h1>Hi there!</h1> <p>I&#39;m Nathanael, a PhD candidate in Aeronautics and Astronautics at the <a href="https://www.mit.edu" target="_blank" rel="noreferrer noopener">Massachusetts Institute of Technology</a>. Welcome to my little space on the web.</p></div></div>  <div style="text-align: center; margin: var(--spacing-16) 0;"><p style="margin-bottom: var(--spacing-6);">Feel free to reach out.</p> <a href="mailto:naj20@mit.edu" class="apple-button" style="text-decoration: none;">naj20@mit.edu</a></div></main>`;
});
export {
  Page as default
};
