export const manifest = (() => {
function __memo(fn) {
	let value;
	return () => value ??= (value = fn());
}

return {
	appDir: "_app",
	appPath: "_app",
	assets: new Set([".DS_Store",".nojekyll","Dogs/Minnie.jpeg","PrivateSamples/CFDGuide.pdf","PrivateSamples/Final.cpp","PrivateSamples/Makefile","PrivateSamples/Original.cpp","PrivateSamples/Original.f90","PrivateSamples/TestingData.xlsx","PrivateSamples/Thesis.pdf","PrivateSamples/rickroll.mp4","Projects/.DS_Store","Projects/AcademicResources/.DS_Store","Projects/AcademicResources/EPQ.pdf","Projects/AcademicResources/FAD_Video.mp4","Projects/AcademicResources/GDP_Report.pdf","Projects/AcademicResources/SnoozeSpiral.pdf","Projects/AcademicResources/UROP_Report.pdf","Projects/AircraftResources/RAM1/RAM1.obj","Projects/AircraftResources/RAM1/RAM1.png","Projects/AircraftResources/RAM1/RAM1.stl","Projects/AircraftResources/RAM1/RAM1.stp","Projects/AircraftResources/RAM2/RAM2.obj","Projects/AircraftResources/RAM2/RAM2.png","Projects/AircraftResources/RAM2/RAM2.stl","Projects/AircraftResources/RAM2/RAM2.stp","Projects/AircraftResources/RAM3/RAM3.obj","Projects/AircraftResources/RAM3/RAM3.png","Projects/AircraftResources/RAM3/RAM3.stl","Projects/AircraftResources/RAM3/RAM3.stp","Projects/AircraftResources/RAM4/RAM4.obj","Projects/AircraftResources/RAM4/RAM4.png","Projects/AircraftResources/RAM4/RAM4.stl","Projects/AircraftResources/RAM4/RAM4.stp","Projects/AircraftResources/RAM5/RAM5.obj","Projects/AircraftResources/RAM5/RAM5.png","Projects/AircraftResources/RAM5/RAM5.stl","Projects/AircraftResources/RAM5/RAM5.stp","Projects/AircraftResources/RAM6/RAM6.obj","Projects/AircraftResources/RAM6/RAM6.png","Projects/AircraftResources/RAM6/RAM6.stl","Projects/AircraftResources/RAM6/RAM6.stp","Projects/FYPResources/NJenkins Thesis Final.pdf","Projects/ICLRResources/APEX.AAE","Projects/ICLRResources/APEX.mp4","Projects/ICLRResources/APEXI.png","Projects/ICLRResources/ASTRA.mp4","Projects/ICLRResources/ASTRA.png","Projects/ICLRResources/ASTRA2.mp4","Projects/ICLRResources/ASTRA3.mp4","Projects/ICLRResources/oR_mF/NSGA_HYBRID.pdf","Projects/ICLRResources/oR_mF/oRmFIntegration.pdf","Projects/ModelResources/AGM-88E.obj","Projects/ModelResources/AGM-88E.pdf","Projects/ModelResources/AGM-88E.png","Projects/ModelResources/AGM-88E.step","Projects/ModelResources/AGM-88E.stl","Projects/ModelResources/AIM-120.obj","Projects/ModelResources/AIM-120.pdf","Projects/ModelResources/AIM-120.png","Projects/ModelResources/AIM-120.step","Projects/ModelResources/AIM-120.stl","Projects/ModelResources/AIM-9X.obj","Projects/ModelResources/AIM-9X.pdf","Projects/ModelResources/AIM-9X.png","Projects/ModelResources/AIM-9X.step","Projects/ModelResources/AIM-9X.stl","Projects/ModelResources/Astra.obj","Projects/ModelResources/Astra.pdf","Projects/ModelResources/Astra.png","Projects/ModelResources/Astra.step","Projects/ModelResources/Astra.stl","Projects/ModelResources/F-106B.obj","Projects/ModelResources/F-106B.pdf","Projects/ModelResources/F-106B.png","Projects/ModelResources/F-106B.step","Projects/ModelResources/F-106B.stl","Projects/PhDResources/.DS_Store","Projects/PhDResources/ESgif.gif","Projects/PhDResources/IEEE_Suppl.pdf","Projects/PhDResources/Overview_Thumbnail.png","Projects/PhDResources/Strike_Mech.png","Projects/PhDResources/Thumbnails/.DS_Store","Projects/PhDResources/Thumbnails/ICOLSE.png","Projects/PhDResources/Thumbnails/IEEE_SHP.png","Projects/PhDResources/Thumbnails/IEEE_Z2.png","Projects/PhDResources/Thumbnails/Suppl.png","Projects/PhDResources/Workflow_Ani.gif","Thumbnails/.DS_Store","Thumbnails/ASTRA.png","Thumbnails/Aircraft.png","Thumbnails/DV_1.png","Thumbnails/DV_2.png","Thumbnails/DV_3.png","Thumbnails/EPQ.png","Thumbnails/FYP.png","Thumbnails/GDP OLD.png","Thumbnails/GDP.png","Thumbnails/Hollowvale.png","Thumbnails/Modelling.png","Thumbnails/PLACEHOLDER.jpeg","Thumbnails/PhD.png","Thumbnails/Snooze.png","Thumbnails/Snooze2.png","Thumbnails/UROP.png","apple-touch-icon-precomposed.png","apple-touch-icon.png","dataviz/A2/1_1_Zip_Matching.png","dataviz/A2/1_2_Zip_Matching_Fixed.png","dataviz/A2/1_3_Corp_Occ.png","dataviz/A2/1_5_Zip_Coverage.png","dataviz/A2/1_6_Census.png","dataviz/A2/1_7_Corp_Occ_Map.png","dataviz/A2/2_1_FilteredMap.png","dataviz/A2/2_2_MapZoomed.png","dataviz/A2/2_3_Prices.png","dataviz/A2/2_4_Age_and_Year.png","dataviz/A2/2_5_Intsqft.png","dataviz/A2/2_6_Investors.png","dataviz/A2/3_1_2.png","dataviz/A2/3_2_1.png","dataviz/A2/3_2_1_0.png","dataviz/A2/3_3_0.png","dataviz/A2/3_3_1.png","dataviz/A2/3_3_2.png","dataviz/A2/3_3_3.png","dataviz/A2/3_4_1.png","dataviz/A3/1_Original.png","dataviz/A3/2_Sketch1.png","dataviz/A3/2_Sketch2.png","dataviz/A3/2_Sketch3.png","dataviz/A3/3_FinalViz.jpg","dataviz/A4/Against.jpg","dataviz/A4/Against_2.jpg","dataviz/A4/Against_3.gif","dataviz/A4/For.jpg","dataviz/A4/For_2.jpg","dataviz/A4/For_3.gif","favicon.ico","google3ed98532692f4666.html","resources-CV/NJenkins CV.pdf","resources-CV/NJenkins Resume.pdf","resources-General/CFD_Dark.gif","resources-General/Git.png","resources-General/In.png","resources-General/Orcid.png","resources-General/Self.jpg","sitemap.xml","styles.css"]),
	mimeTypes: {".jpeg":"image/jpeg",".pdf":"application/pdf",".mp4":"video/mp4",".obj":"model/obj",".png":"image/png",".stl":"model/stl",".gif":"image/gif",".jpg":"image/jpeg",".html":"text/html",".xml":"application/xml",".css":"text/css"},
	_: {
		client: {"start":"_app/immutable/entry/start.3382ae54.js","app":"_app/immutable/entry/app.c330a330.js","imports":["_app/immutable/entry/start.3382ae54.js","_app/immutable/chunks/scheduler.14a511a7.js","_app/immutable/chunks/singletons.d4346ca1.js","_app/immutable/chunks/paths.f4401a76.js","_app/immutable/entry/app.c330a330.js","_app/immutable/chunks/scheduler.14a511a7.js","_app/immutable/chunks/index.2d17dc57.js"],"stylesheets":[],"fonts":[]},
		nodes: [
			__memo(() => import('./nodes/0.js')),
			__memo(() => import('./nodes/1.js')),
			__memo(() => import('./nodes/2.js')),
			__memo(() => import('./nodes/3.js')),
			__memo(() => import('./nodes/4.js')),
			__memo(() => import('./nodes/5.js')),
			__memo(() => import('./nodes/6.js')),
			__memo(() => import('./nodes/7.js')),
			__memo(() => import('./nodes/8.js')),
			__memo(() => import('./nodes/9.js')),
			__memo(() => import('./nodes/10.js')),
			__memo(() => import('./nodes/11.js')),
			__memo(() => import('./nodes/12.js')),
			__memo(() => import('./nodes/13.js')),
			__memo(() => import('./nodes/14.js')),
			__memo(() => import('./nodes/15.js')),
			__memo(() => import('./nodes/16.js')),
			__memo(() => import('./nodes/17.js')),
			__memo(() => import('./nodes/18.js')),
			__memo(() => import('./nodes/19.js'))
		],
		routes: [
			{
				id: "/",
				pattern: /^\/$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 2 },
				endpoint: null
			},
			{
				id: "/404",
				pattern: /^\/404\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 3 },
				endpoint: null
			},
			{
				id: "/CV",
				pattern: /^\/CV\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 4 },
				endpoint: null
			},
			{
				id: "/Projects",
				pattern: /^\/Projects\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 5 },
				endpoint: null
			},
			{
				id: "/Projects/Academic",
				pattern: /^\/Projects\/Academic\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 6 },
				endpoint: null
			},
			{
				id: "/Projects/Academic/EPQ",
				pattern: /^\/Projects\/Academic\/EPQ\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 7 },
				endpoint: null
			},
			{
				id: "/Projects/Academic/GDP",
				pattern: /^\/Projects\/Academic\/GDP\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 8 },
				endpoint: null
			},
			{
				id: "/Projects/Academic/SnoozeSpiral",
				pattern: /^\/Projects\/Academic\/SnoozeSpiral\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 9 },
				endpoint: null
			},
			{
				id: "/Projects/Academic/UROP",
				pattern: /^\/Projects\/Academic\/UROP\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 10 },
				endpoint: null
			},
			{
				id: "/Projects/Aircraft",
				pattern: /^\/Projects\/Aircraft\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 11 },
				endpoint: null
			},
			{
				id: "/Projects/ICLR",
				pattern: /^\/Projects\/ICLR\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 12 },
				endpoint: null
			},
			{
				id: "/Projects/Modelling",
				pattern: /^\/Projects\/Modelling\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 13 },
				endpoint: null
			},
			{
				id: "/Projects/PhD",
				pattern: /^\/Projects\/PhD\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 14 },
				endpoint: null
			},
			{
				id: "/Projects/Thesis",
				pattern: /^\/Projects\/Thesis\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 15 },
				endpoint: null
			},
			{
				id: "/dataviz",
				pattern: /^\/dataviz\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 16 },
				endpoint: null
			},
			{
				id: "/dataviz/A2",
				pattern: /^\/dataviz\/A2\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 17 },
				endpoint: null
			},
			{
				id: "/dataviz/A3",
				pattern: /^\/dataviz\/A3\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 18 },
				endpoint: null
			},
			{
				id: "/dataviz/A4",
				pattern: /^\/dataviz\/A4\/?$/,
				params: [],
				page: { layouts: [0,], errors: [1,], leaf: 19 },
				endpoint: null
			}
		],
		matchers: async () => {
			
			return {  };
		}
	}
}
})();
