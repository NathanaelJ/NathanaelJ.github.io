// Prerendered at build time: a static SVG thumbnail for the Projects grid that stays in sync with travels.json.
import { geoEqualEarth, geoPath } from 'd3';
import { feature } from 'topojson-client';
import world from 'world-atlas/countries-110m.json';
import { loadTravels } from '$lib/server/travels.js';
import { COLORS, dropAntarctica, featureId, flightPath } from '$lib/travels/geo.js';

export const prerender = true;

export function GET() {
    const { countries, routes, airports } = loadTravels();
    const visited = new Set(countries);

    const W = 680;
    const H = 400;
    const features = dropAntarctica(feature(world, world.objects.countries).features, visited);
    const collection = { type: 'FeatureCollection', features };
    const projection = geoEqualEarth().fitExtent([[20, 20], [W - 20, H - 20]], collection);
    const path = geoPath(projection);

    const shapes = features
        .map((f) => ({ d: path(f), visited: visited.has(featureId(f)) }))
        .sort((a, b) => a.visited - b.visited)
        .map((s) =>
            s.visited
                ? `<path d="${s.d}" fill="${COLORS.visited}" stroke="${COLORS.visitedOutline}" stroke-width="0.6"/>`
                : `<path d="${s.d}" fill="none" stroke="${COLORS.outline}" stroke-width="0.6"/>`
        )
        .join('');

    const flights = routes
        .map((r) => flightPath(projection, [airports[r.a].lon, airports[r.a].lat], [airports[r.b].lon, airports[r.b].lat]))
        .filter(Boolean)
        .map((d) => `<path d="${d}" fill="none" stroke="${COLORS.flight}" stroke-width="1.4" stroke-linecap="round" stroke-opacity="0.75"/>`)
        .join('');

    const svg = `<svg xmlns="http://www.w3.org/2000/svg" width="${W}" height="${H}" viewBox="0 0 ${W} ${H}"><g stroke-linejoin="round">${shapes}</g>${flights}</svg>`;

    return new Response(svg, { headers: { 'Content-Type': 'image/svg+xml' } });
}
