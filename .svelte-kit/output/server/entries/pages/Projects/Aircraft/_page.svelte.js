import { c as create_ssr_component, e as escape, f as add_attribute, d as each, v as validate_component } from "../../../../chunks/ssr.js";
import { M as MissileModel } from "../../../../chunks/MissileModel.js";
const deltaDart = [
  {
    id: "F-106B",
    name: "F-106 Delta Dart",
    description: "This was modeled after the F-106B Delta Dart, using open-source data.",
    downloads: {
      step: "ModelResources/F-106B.step",
      stl: "ModelResources/F-106B.stl",
      obj: "ModelResources/F-106B.obj",
      pdf: "ModelResources/F-106B.pdf"
    },
    image: "ModelResources/F-106B.png",
    alt: "F-106B Delta Dart"
  }
];
const AircraftModel = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  let { aircraft: aircraft2 } = $$props;
  let { animationDelay = "0s" } = $$props;
  if ($$props.aircraft === void 0 && $$bindings.aircraft && aircraft2 !== void 0)
    $$bindings.aircraft(aircraft2);
  if ($$props.animationDelay === void 0 && $$bindings.animationDelay && animationDelay !== void 0)
    $$bindings.animationDelay(animationDelay);
  return `<div class="project-section fade-in-up liquid-glass" style="${"animation-delay: " + escape(animationDelay, true) + ";"}"><h3${add_attribute("id", aircraft2.id, 0)}>${escape(aircraft2.name)}</h3> ${aircraft2.description ? `<p>${escape(aircraft2.description)}</p>` : ``} <div class="download-buttons"><a${add_attribute("href", aircraft2.downloads.step, 0)} download class="download-btn liquid-glass">Download STEP</a> <a${add_attribute("href", aircraft2.downloads.stl, 0)} download class="download-btn liquid-glass">Download STL (Binary)</a> <a${add_attribute("href", aircraft2.downloads.obj, 0)} download class="download-btn liquid-glass">Download OBJ</a> <a${add_attribute("href", aircraft2.downloads.pdf, 0)} download class="download-btn liquid-glass">Download drawing (PDF)</a></div> <div class="image-container liquid-glass"><img${add_attribute("src", aircraft2.image, 0)}${add_attribute("alt", aircraft2.alt, 0)}></div></div>`;
});
const aircraft = [
  {
    id: "AGM-88E",
    name: "AGM-88E AARGM",
    description: "",
    downloads: {
      step: "ModelResources/AGM-88E.step",
      stl: "ModelResources/AGM-88E.stl",
      obj: "ModelResources/AGM-88E.obj",
      pdf: "ModelResources/AGM-88E.pdf"
    },
    image: "ModelResources/AGM-88E.png",
    alt: "AGM-88E AARGM"
  },
  {
    id: "AIM-120",
    name: "AIM-120A AMRAAM",
    description: "",
    downloads: {
      step: "ModelResources/AIM-120.step",
      stl: "ModelResources/AIM-120.stl",
      obj: "ModelResources/AIM-120.obj",
      pdf: "ModelResources/AIM-120.pdf"
    },
    image: "ModelResources/AIM-120.png",
    alt: "AIM-120A AMRAAM"
  },
  {
    id: "AIM-9X",
    name: "AIM-9X Sidewinder",
    description: "The launch rail in this model is based on the design used for attachment to the F-16 (under-wing). Different geometries are used for other aircraft. This missile is sometimes mounted at the wing tips (e.g. F-18D). 3D files include the launch rail; dimensioned drawings show the missile body only.",
    downloads: {
      step: "ModelResources/AIM-9X.step",
      stl: "ModelResources/AIM-9X.stl",
      obj: "ModelResources/AIM-9X.obj",
      pdf: "ModelResources/AIM-9X.pdf"
    },
    image: "ModelResources/AIM-9X.png",
    alt: "AIM-9X Sidewinder"
  },
  {
    id: "Astra-Mk1",
    name: "Astra-Mk1",
    description: "3D files include the launch rail; dimensioned drawings show the missile body only.",
    downloads: {
      step: "ModelResources/Astra.step",
      stl: "ModelResources/Astra.stl",
      obj: "ModelResources/Astra.obj",
      pdf: "ModelResources/Astra.pdf"
    },
    image: "ModelResources/Astra.png",
    alt: "Astra Mk.1"
  }
];
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  return `${$$result.head += `<!-- HEAD_svelte-1ccqm6r_START -->${$$result.title = `<title>Aircraft | N Jenkins</title>`, ""}<!-- HEAD_svelte-1ccqm6r_END -->`, ""} <main class="site-main modelling-page"><div class="wrapper"><div class="page-header fade-in-up liquid-glass"><h1 data-svelte-h="svelte-tgxcf6">Aircraft Models</h1> <p data-svelte-h="svelte-rjgtxp">TEXT GOES HERE.<br><br></p> <p data-svelte-h="svelte-1u1gg8u">I&#39;m often frustrated by high download costs for seemingly simple CAD models so want to make these models available for hobbyists for free. For commercial use, please <a href="mailto:naj20@mit.edu">contact me</a> first.<br><br></p> <p>${each(aircraft, (plane) => {
    return `<a href="${"#" + escape(plane.id, true)}">${escape(plane.name)}</a><br>`;
  })} <a href="#F-106B" data-svelte-h="svelte-1mhqxm0">F-106B Delta Dart</a></p></div> ${each(aircraft, (plane, index) => {
    return `${validate_component(AircraftModel, "AircraftModel").$$render(
      $$result,
      {
        plane,
        animationDelay: (index + 1) * 0.2 + 0.4 + "s"
      },
      {},
      {}
    )}`;
  })} ${each(deltaDart, (dart, index) => {
    return `${validate_component(MissileModel, "MissileModel").$$render($$result, { dart, animationDelay: 0.2 + "s" }, {}, {})}`;
  })}</div></main>`;
});
export {
  Page as default
};
