import { c as create_ssr_component, f as add_attribute, e as escape } from "./ssr.js";
import { b as base } from "./paths.js";
const void_element_names = /^(?:area|base|br|col|command|embed|hr|img|input|keygen|link|meta|param|source|track|wbr)$/;
function is_void(name) {
  return void_element_names.test(name) || name.toLowerCase() === "!doctype";
}
const ProjectCard_svelte_svelte_type_style_lang = "";
const css = {
  code: ".project-card.svelte-1winfil{background:var(--color-background);border-radius:8px;overflow:hidden;transition:transform 0.2s;box-shadow:0 2px 5px var(--color-border)}.project-card.svelte-1winfil:hover{transform:translateY(-5px)}",
  map: null
};
const ProjectCard = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let { data = {} } = $$props;
  let { hLevel = 2 } = $$props;
  if ($$props.data === void 0 && $$bindings.data && data !== void 0)
    $$bindings.data(data);
  if ($$props.hLevel === void 0 && $$bindings.hLevel && hLevel !== void 0)
    $$bindings.hLevel(hLevel);
  $$result.css.add(css);
  return `<article class="project-card svelte-1winfil"><img${add_attribute("src", data.img, 0)} alt="Project Thumbnail" class="project-image"> <div class="project-content">${((tag) => {
    return tag ? `<${"h" + hLevel}>${is_void(tag) ? "" : `${escape(data.title)}`}${is_void(tag) ? "" : `</${tag}>`}` : "";
  })("h" + hLevel)} <h3>${escape(data.subtitle)}</h3> <p>${escape(data.year)}</p> <p>${escape(data.description)}</p> <a href="${escape(base, true) + "/" + escape(data.link, true)}" class="project-link">View Project</a></div> </article>`;
});
export {
  ProjectCard as P
};
