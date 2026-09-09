import { c as create_ssr_component, f as add_attribute, e as escape } from "./ssr.js";
import { b as base } from "./paths.js";
const void_element_names = /^(?:area|base|br|col|command|embed|hr|img|input|keygen|link|meta|param|source|track|wbr)$/;
function is_void(name) {
  return void_element_names.test(name) || name.toLowerCase() === "!doctype";
}
const ProjectCard = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let projectLink;
  let isExternal;
  let { data = {} } = $$props;
  let { hLevel = 2 } = $$props;
  if ($$props.data === void 0 && $$bindings.data && data !== void 0)
    $$bindings.data(data);
  if ($$props.hLevel === void 0 && $$bindings.hLevel && hLevel !== void 0)
    $$bindings.hLevel(hLevel);
  projectLink = data.link.startsWith("external:") ? data.link.replace("external:", "") : `${base}/${data.link}`;
  isExternal = data.link.startsWith("external:");
  return `<article class="project-card"><a${add_attribute("href", projectLink, 0)}${add_attribute("target", isExternal ? "_blank" : void 0, 0)}${add_attribute("rel", isExternal ? "noopener noreferrer" : void 0, 0)}><img${add_attribute("src", data.img, 0)} alt="Project Thumbnail" class="project-image"> <div class="project-content"><div class="position-line">${((tag) => {
    return tag ? `<${"h" + hLevel}>${is_void(tag) ? "" : `${escape(data.title)}`}${is_void(tag) ? "" : `</${tag}>`}` : "";
  })("h" + hLevel)} <span class="date-range">${escape(data.year)}</span></div> <h3>${escape(data.subtitle)}</h3> </div></a></article>`;
});
export {
  ProjectCard as P
};
