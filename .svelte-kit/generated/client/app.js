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
	() => import('./nodes/19'),
	() => import('./nodes/20')
];

export const server_loads = [];

export const dictionary = {
		"/": [2],
		"/404": [3],
		"/CV": [4],
		"/Projects": [5],
		"/Projects/Academic": [6],
		"/Projects/Academic/AI": [7],
		"/Projects/Academic/EPQ": [8],
		"/Projects/Academic/GDP": [9],
		"/Projects/Academic/SnoozeSpiral": [10],
		"/Projects/Academic/UROP": [11],
		"/Projects/Aircraft": [12],
		"/Projects/ICLR": [13],
		"/Projects/Modelling": [14],
		"/Projects/PhD": [15],
		"/Projects/Thesis": [16],
		"/dataviz": [17],
		"/dataviz/A2": [18],
		"/dataviz/A3": [19],
		"/dataviz/A4": [20]
	};

export const hooks = {
	handleError: (({ error }) => { console.error(error) }),
};

export { default as root } from '../root.svelte';