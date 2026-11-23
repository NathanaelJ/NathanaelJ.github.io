// Shared drawing helpers for the Travels page and its build-time thumbnail.
import { geoPath } from 'd3';

export const COLORS = {
    background: '#f0e8dd',
    outline: '#b3aba0',
    visited: '#a8743f',
    visitedOutline: '#8a5e31',
    flight: '#182019'
};

// Antarctica takes a lot of room and nobody is flying there (yet) — drop it unless visited.
export function dropAntarctica(features, visited = new Set()) {
    return features.filter((f) => f.id !== '010' || visited.has('010'));
}

// Natural Earth abbreviates long names to fit printed maps; spell them out for tooltips.
const FULL_NAMES = {
    'Marshall Is.': 'Marshall Islands',
    'N. Mariana Is.': 'Northern Mariana Islands',
    'U.S. Virgin Is.': 'U.S. Virgin Islands',
    'S. Geo. and the Is.': 'South Georgia and the South Sandwich Islands',
    'Br. Indian Ocean Ter.': 'British Indian Ocean Territory',
    'Pitcairn Is.': 'Pitcairn Islands',
    'Falkland Is.': 'Falkland Islands',
    'Cayman Is.': 'Cayman Islands',
    'British Virgin Is.': 'British Virgin Islands',
    'Turks and Caicos Is.': 'Turks and Caicos Islands',
    'S. Sudan': 'South Sudan',
    'Solomon Is.': 'Solomon Islands',
    'St. Vin. and Gren.': 'Saint Vincent and the Grenadines',
    'St. Kitts and Nevis': 'Saint Kitts and Nevis',
    'Cook Is.': 'Cook Islands',
    'W. Sahara': 'Western Sahara',
    'St. Pierre and Miquelon': 'Saint Pierre and Miquelon',
    'Wallis and Futuna Is.': 'Wallis and Futuna',
    'Fr. Polynesia': 'French Polynesia',
    'Fr. S. Antarctic Lands': 'French Southern and Antarctic Lands',
    'Eq. Guinea': 'Equatorial Guinea',
    'Dominican Rep.': 'Dominican Republic',
    'Faeroe Is.': 'Faroe Islands',
    'N. Cyprus': 'Northern Cyprus',
    'Dem. Rep. Congo': 'Democratic Republic of the Congo',
    'Central African Rep.': 'Central African Republic',
    'Bosnia and Herz.': 'Bosnia and Herzegovina',
    'Indian Ocean Ter.': 'Australian Indian Ocean Territories',
    'Heard I. and McDonald Is.': 'Heard Island and McDonald Islands',
    'Ashmore and Cartier Is.': 'Ashmore and Cartier Islands',
    'Antigua and Barb.': 'Antigua and Barbuda',
    'United States of America': 'United States'
};

export function featureName(f) {
    const name = f.properties?.name ?? '';
    return FULL_NAMES[name] ?? name;
}

// Some Natural Earth features (Kosovo, N. Cyprus, ...) have no ISO id; fall back to their name.
export function featureId(f) {
    return f.id ?? f.properties?.name;
}

/**
 * SVG path for a flight between two [lon, lat] points.
 * Draws a gentle screen-space arc that bows "upwards", like a route map. If the shortest
 * path crosses the antimeridian (e.g. across the Pacific) a screen-space arc would cut the
 * wrong way across the map, so the true great circle is drawn instead.
 */
export function flightPath(projection, from, to, bend = 0.22) {
    const p0 = projection(from);
    const p1 = projection(to);
    if (!p0 || !p1) return null;

    if (Math.abs(from[0] - to[0]) > 180) {
        return geoPath(projection)({ type: 'LineString', coordinates: [from, to] });
    }

    const [x0, y0] = p0;
    const [x1, y1] = p1;
    const dx = x1 - x0;
    const dy = y1 - y0;
    const dist = Math.hypot(dx, dy);
    // Unit normal, flipped so the arc always bows towards the top of the map
    let nx = -dy / dist;
    let ny = dx / dist;
    if (ny > 0) {
        nx = -nx;
        ny = -ny;
    }
    const cx = (x0 + x1) / 2 + nx * dist * bend;
    const cy = (y0 + y1) / 2 + ny * dist * bend;
    const r = (n) => Math.round(n * 10) / 10;
    return `M${r(x0)},${r(y0)}Q${r(cx)},${r(cy)} ${r(x1)},${r(y1)}`;
}
