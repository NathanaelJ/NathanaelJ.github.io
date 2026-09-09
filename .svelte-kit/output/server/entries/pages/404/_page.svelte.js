import { c as create_ssr_component, e as escape } from "../../../chunks/ssr.js";
import { b as base } from "../../../chunks/paths.js";
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  return `${$$result.head += `<!-- HEAD_svelte-1be2w2h_START -->${$$result.title = `<title>404: Page Not Found</title>`, ""}<!-- HEAD_svelte-1be2w2h_END -->`, ""} <main class="site-main" data-svelte-h="svelte-1q45cyf"><div class="wrapper"><div class="error-container fade-in-up"><h1>404: Page Not Found</h1></div> <div class="intro-container fade-in-up" style="animation-delay: 0.2s;"><div class="intro-text"><p>Oops! It looks like you&#39;ve wandered into uncharted territory. While you&#39;re here, enjoy this photo of Minnie the dog.</p></div> <figure><img src="${escape(base, true) + "/Dogs/Minnie.jpeg"}" alt="Minnie the dog" class="introimg"></figure></div> <div class="text-center" style="margin-top: 2em;"><a href="${escape(base, true) + "/"}" class="project-link">Return to Homepage</a></div></div></main>`;
});
export {
  Page as default
};
