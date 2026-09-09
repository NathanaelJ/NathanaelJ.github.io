import { c as create_ssr_component, e as escape, f as add_attribute } from "./ssr.js";
import { b as base } from "./paths.js";
const MissileModel = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let { missile } = $$props;
  let { animationDelay = "0s" } = $$props;
  if ($$props.missile === void 0 && $$bindings.missile && missile !== void 0)
    $$bindings.missile(missile);
  if ($$props.animationDelay === void 0 && $$bindings.animationDelay && animationDelay !== void 0)
    $$bindings.animationDelay(animationDelay);
  return `<div class="project-section fade-in-up liquid-glass" style="${"animation-delay: " + escape(animationDelay, true) + ";"}"><h3${add_attribute("id", missile.id, 0)}>${escape(missile.name)}</h3> ${missile.description ? `<p><!-- HTML_TAG_START -->${missile.description}<!-- HTML_TAG_END --></p>` : ``} <div class="download-buttons"><a${add_attribute("href", missile.downloads.step, 0)} download class="download-btn liquid-glass">Download STEP</a> <a${add_attribute("href", missile.downloads.stl, 0)} download class="download-btn liquid-glass">Download STL (Binary)</a> <a${add_attribute("href", missile.downloads.obj, 0)} download class="download-btn liquid-glass">Download OBJ</a> <a${add_attribute("href", missile.downloads.pdf, 0)} download class="download-btn liquid-glass">Download drawing (PDF)</a></div> <div class="image-container liquid-glass"><img src="${escape(base, true) + "/Projects/" + escape(missile.image, true)}"${add_attribute("alt", missile.alt, 0)}></div></div>`;
});
export {
  MissileModel as M
};
