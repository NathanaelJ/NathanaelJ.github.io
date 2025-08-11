export { matchers } from './matchers.js';

export const nodes = [
	() => import('./nodes/0'),
	() => import('./nodes/1'),
	() => import('./nodes/2'),
	() => import('./nodes/3'),
	() => import('./nodes/4'),
	() => import('./nodes/5'),
	() => import('./nodes/6'),
	() => import('./nodes/7'),
	() => import('./nodes/8'),
	() => import('./nodes/9'),
	() => import('./nodes/10'),
	() => import('./nodes/11'),
	() => import('./nodes/12'),
	() => import('./nodes/13'),
	() => import('./nodes/14')
];

export const server_loads = [];

export const dictionary = {
		"/": [2],
		"/404": [3],
		"/Projects": [4],
		"/Projects/Academic": [5],
		"/Projects/ICLR": [6],
		"/Projects/Modelling": [7],
		"/Projects/Thesis": [8],
		"/dataviz": [9],
		"/dataviz/A2": [10],
		"/dataviz/A3": [11],
		"/dataviz/A4": [12],
		"/dataviz/contact": [13],
		"/resume": [14]
	};

export const hooks = {
	handleError: (({ error }) => { console.error(error) }),
};

export { default as root } from '../root.svelte';