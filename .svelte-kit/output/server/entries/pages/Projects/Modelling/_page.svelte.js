import { c as create_ssr_component, d as each, e as escape, v as validate_component } from "../../../../chunks/ssr.js";
import { M as MissileModel } from "../../../../chunks/MissileModel.js";
const missiles = [
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
  return `${$$result.head += `<!-- HEAD_svelte-c6lhp8_START -->${$$result.title = `<title>Modelling | N Jenkins</title>`, ""}<!-- HEAD_svelte-c6lhp8_END -->`, ""} <main class="site-main modelling-page"><div class="wrapper"><div class="page-header fade-in-up liquid-glass"><h1 data-svelte-h="svelte-1p0azqq">Missile Models</h1> <p data-svelte-h="svelte-bpn97k">All of the data relating to these models was taken from publicly available data, predominantly photos published by militaries or manufacturers. While I&#39;ve done my best to create models which are as accurate as possible, differences are inevitable.<br><br></p> <p data-svelte-h="svelte-1u1gg8u">I&#39;m often frustrated by high download costs for seemingly simple CAD models so want to make these models available for hobbyists for free. For commercial use, please <a href="mailto:naj20@mit.edu">contact me</a> first.<br><br></p> <p>${each(missiles, (missile) => {
    return `<a href="${"#" + escape(missile.id, true)}">${escape(missile.name)}</a><br>`;
  })}</p></div> ${each(missiles, (missile, index) => {
    return `${validate_component(MissileModel, "MissileModel").$$render(
      $$result,
      {
        missile,
        animationDelay: (index + 1) * 0.2 + 0.4 + "s"
      },
      {},
      {}
    )}`;
  })}</div></main>`;
});
export {
  Page as default
};
