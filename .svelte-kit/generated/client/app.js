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
	() => import('./nodes/17'),
	() => import('./nodes/18'),
	() => import('./nodes/19')
];

export const server_loads = [];

export const dictionary = {
		"/": [2],
		"/404": [3],
		"/Projects": [4],
		"/Projects/Academic": [5],
		"/Projects/Academic/EPQ": [6],
		"/Projects/Academic/GDP": [7],
		"/Projects/Academic/SnoozeSpiral": [8],
		"/Projects/Academic/UROP": [9],
		"/Projects/Aircraft": [10],
		"/Projects/ICLR": [11],
		"/Projects/Modelling": [12],
		"/Projects/PhD": [13],
		"/Projects/Thesis": [14],
		"/dataviz": [15],
		"/dataviz/A2": [16],
		"/dataviz/A3": [17],
		"/dataviz/A4": [18],
		"/resume": [19]
	};

export const hooks = {
	handleError: (({ error }) => { console.error(error) }),
};

export { default as root } from '../root.svelte';