import { c as create_ssr_component, e as escape, f as add_attribute, d as each, v as validate_component } from "../../../../chunks/ssr.js";
import { b as base } from "../../../../chunks/paths.js";
import { M as MissileModel } from "../../../../chunks/MissileModel.js";
const deltaDart = [
  {
    id: "F-106B",
    name: "F-106 Delta Dart",
    description: "This was modeled after the F-106B Delta Dart, using open-source data. It is used in <a href='https://ieeexplore.ieee.org/document/10792439' target='_blank' rel='noreferrer noopener'>this paper.</a>",
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
  return `<div class="aircraft-card " style="${"animation-delay: " + escape(animationDelay, true) + ";"}"><div class="image-container "><img src="${escape(base, true) + "/Projects/" + escape(aircraft2.image, true)}"${add_attribute("alt", aircraft2.alt, 0)}></div> <div class="card-content"><h3${add_attribute("id", aircraft2.id, 0)}>${escape(aircraft2.name)}</h3> ${aircraft2.description ? `<p>${escape(aircraft2.description)}</p>` : ``} <div class="download-buttons"><a${add_attribute("href", aircraft2.link, 0)} target="_blank" class="download-btn ">⇱ OpenVSP</a> <a${add_attribute("href", aircraft2.downloads.stp, 0)} download class="download-btn ">Download STP</a> <a${add_attribute("href", aircraft2.downloads.stl, 0)} download class="download-btn ">Download STL</a> <a${add_attribute("href", aircraft2.downloads.obj, 0)} download class="download-btn ">Download OBJ</a></div></div></div>`;
});
const aircraft = [
  {
    id: "RAM1",
    name: "RAM 1: Small Transport Jet",
    description: "",
    link: "https://airshow.openvsp.org/vsp/MF3LYK6uewre88GZ6AtM",
    downloads: {
      stp: "AircraftResources/RAM1/RAM1.stp",
      stl: "AircraftResources/RAM1/RAM1.stl",
      obj: "AircraftResources/RAM1/RAM1.obj"
    },
    image: "AircraftResources/RAM1/RAM1.png",
    alt: "RAM 1: Small Transport Jet"
  },
  {
    id: "RAM2",
    name: "RAM 2: Large Transport Jet",
    description: "",
    link: "https://airshow.openvsp.org/vsp/AIM94tGYzgoGaU61inPi",
    downloads: {
      stp: "AircraftResources/RAM2/RAM2.stp",
      stl: "AircraftResources/RAM2/RAM2.stl",
      obj: "AircraftResources/RAM2/RAM2.obj"
    },
    image: "AircraftResources/RAM2/RAM2.png",
    alt: "RAM 2: Large Transport Jet"
  },
  {
    id: "RAM3",
    name: "RAM 3: Transport Prop",
    description: "",
    link: "https://airshow.openvsp.org/vsp/F22NcQbEY0dhW1Mo32EM",
    downloads: {
      stp: "AircraftResources/RAM3/RAM3.stp",
      stl: "AircraftResources/RAM3/RAM3.stl",
      obj: "AircraftResources/RAM3/RAM3.obj"
    },
    image: "AircraftResources/RAM3/RAM3.png",
    alt: "RAM 3: Transport Prop"
  },
  {
    id: "RAM4",
    name: "RAM 4: Transport Helicopter",
    description: "",
    link: "https://airshow.openvsp.org/vsp/mY3Ea0Yle3SAOds9kPDf",
    downloads: {
      stp: "AircraftResources/RAM4/RAM4.stp",
      stl: "AircraftResources/RAM4/RAM4.stl",
      obj: "AircraftResources/RAM4/RAM4.obj"
    },
    image: "AircraftResources/RAM4/RAM4.png",
    alt: "RAM 4: Transport Helicopter"
  },
  {
    id: "RAM5",
    name: "RAM 5: Blended Wing Concept",
    description: "",
    link: "https://airshow.openvsp.org/vsp/eDwg65Fo54BE9UuNEiZz",
    downloads: {
      stp: "AircraftResources/RAM5/RAM5.stp",
      stl: "AircraftResources/RAM5/RAM5.stl",
      obj: "AircraftResources/RAM5/RAM5.obj"
    },
    image: "AircraftResources/RAM5/RAM5.png",
    alt: "RAM 5: Blended Wing Concept"
  },
  {
    id: "RAM6",
    name: "RAM 6: eVTOL Concept",
    description: "",
    link: "https://airshow.openvsp.org",
    downloads: {
      stp: "AircraftResources/RAM6/RAM6.stp",
      stl: "AircraftResources/RAM6/RAM6.stl",
      obj: "AircraftResources/RAM6/RAM6.obj"
    },
    image: "AircraftResources/RAM6/RAM6.png",
    alt: "RAM 6: eVTOL Concept"
  }
];
const Page = create_ssr_component(($$result, $$props, $$bindings, slots) => {
  return `${$$result.head += `<!-- HEAD_svelte-1ccqm6r_START -->${$$result.title = `<title>Aircraft | N Jenkins</title>`, ""}<!-- HEAD_svelte-1ccqm6r_END -->`, ""} <main class="site-main modelling-page"><div class="wrapper"><div class="page-header  " data-svelte-h="svelte-1fdmere"><h1>Aircraft Models</h1> <p>I created these concept-level aircraft models to support my <a href="${escape(base, true) + "/Projects/PhD"}">PhD</a> research.<br>Free to use for non-commercial purposes.</p> </div> <div class="aircraft-grid">${each(aircraft, (plane, index) => {
    return `${validate_component(AircraftModel, "AircraftModel").$$render(
      $$result,
      {
        aircraft: plane,
        animationDelay: (index + 1) * 0.2 + 0.4 + "s"
      },
      {},
      {}
    )}`;
  })}</div> ${each(deltaDart, (dart, index) => {
    return `${validate_component(MissileModel, "MissileModel").$$render($$result, { missile: dart, animationDelay: 0.2 + "s" }, {}, {})}`;
  })}</div></main>`;
});
export {
  Page as default
};
