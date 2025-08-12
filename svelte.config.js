import adapter from '@sveltejs/adapter-static';

/** @type {import('@sveltejs/kit').Config} */
const config = {
	onwarn: (warning, handler) => {
		// suppress warnings on `vite dev` and `vite build`; but even without this, things still work
		if (warning.code === "a11y-click-events-have-key-events") return;
		if (warning.code === "a11y-no-static-element-interactions") return;
		if (warning.code === "a11y-figcaption") return;
		handler(warning);
	},
	kit: {
		adapter: adapter({ fallback: '404.html' }),
		paths: {
			// User/Org GitHub Pages at username.github.io are hosted at root, so no base path
			base: ''
		},
	},
};

export default config;