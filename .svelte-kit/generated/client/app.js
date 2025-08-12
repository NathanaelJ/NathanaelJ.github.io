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
	() => import('./nodes/14'),
	() => import('./nodes/15'),
	() => import('./nodes/16'),
	() => import('./nodes/17')
];

export const server_loads = [];

export const dictionary = {
		"/": [2],
		"/404": [3],
		"/Projects": [4],
		"/Projects/Academic": [5],
		"/Projects/Academic/EPQ": [6],
		"/Projects/Academic/GDP": [7],
		"/Projects/Academic/UROP": [8],
		"/Projects/ICLR": [9],
		"/Projects/Modelling": [10],
		"/Projects/Thesis": [11],
		"/dataviz": [12],
		"/dataviz/A2": [13],
		"/dataviz/A3": [14],
		"/dataviz/A4": [15],
		"/dataviz/contact": [16],
		"/resume": [17]
	};

export const hooks = {
	handleError: (({ error }) => { console.error(error) }),
};

export { default as root } from '../root.svelte';