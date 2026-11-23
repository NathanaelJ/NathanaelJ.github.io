// Build-time only: resolves src/lib/travels.json into the compact data the Travels page draws.
// Lives in $lib/server so the full airport/country tables are never shipped to visitors.
import travels from '$lib/travels.json';
import airports from '$lib/travels/airports.json';
import countryTable from '$lib/travels/countries.json';

export const TOTAL_COUNTRIES = 195;
export const TOTAL_STATES = 50;

// USPS code -> FIPS id used by us-atlas (DC is drawn if listed, but not counted as a state)
const STATES = {
    AL: '01', AK: '02', AZ: '04', AR: '05', CA: '06', CO: '08', CT: '09', DE: '10', DC: '11',
    FL: '12', GA: '13', HI: '15', ID: '16', IL: '17', IN: '18', IA: '19', KS: '20', KY: '21',
    LA: '22', ME: '23', MD: '24', MA: '25', MI: '26', MN: '27', MS: '28', MO: '29', MT: '30',
    NE: '31', NV: '32', NH: '33', NJ: '34', NM: '35', NY: '36', NC: '37', ND: '38', OH: '39',
    OK: '40', OR: '41', PA: '42', RI: '44', SC: '45', SD: '46', TN: '47', TX: '48', UT: '49',
    VT: '50', VA: '51', WA: '53', WV: '54', WI: '55', WY: '56'
};

const countryLookup = new Map();
for (const [a2, a3, num, name] of countryTable) {
    for (const key of [a2, a3, name]) countryLookup.set(key.toUpperCase(), num);
}

function warn(msg) {
    console.warn(`[travels.json] ${msg}`);
}

function resolveCountries(list = []) {
    const ids = new Set();
    for (const entry of list) {
        const id = countryLookup.get(String(entry).trim().toUpperCase());
        if (id) ids.add(id);
        else warn(`unknown country "${entry}" (use a 2- or 3-letter ISO code, e.g. "GB" or "GBR")`);
    }
    return [...ids];
}

function resolveStates(list = []) {
    const ids = new Set();
    for (const entry of list) {
        const id = STATES[String(entry).trim().toUpperCase()];
        if (id) ids.add(id);
        else warn(`unknown state "${entry}" (use a 2-letter postal code, e.g. "MA")`);
    }
    return [...ids];
}

function cityOf(code) {
    const [, , name, municipality] = airports[code];
    // "Paris (Roissy-en-France, Val-d'Oise)" -> "Paris"
    return (municipality || name).replace(/\s*\(.*\)\s*$/, '');
}

function resolveFlights(list = []) {
    const routes = new Map();
    const used = new Set();
    for (const entry of list) {
        const [from, to] = String(entry).toUpperCase().split(/[^A-Z]+/).filter(Boolean);
        if (!from || !to || from === to) {
            warn(`could not read flight "${entry}" (expected "BOS-LHR")`);
            continue;
        }
        const missing = [from, to].filter((c) => !airports[c]);
        if (missing.length) {
            warn(`unknown airport code ${missing.join(', ')} in "${entry}"`);
            continue;
        }
        // One route per airport pair, counting each direction separately
        const [a, b] = [from, to].sort();
        const key = `${a}-${b}`;
        if (!routes.has(key)) routes.set(key, { a, b, counts: { [a]: 0, [b]: 0 } });
        routes.get(key).counts[from] += 1;
        used.add(from).add(to);
    }

    const airportData = {};
    for (const code of used) {
        const [lat, lon, name] = airports[code];
        airportData[code] = { lat, lon, name, city: cityOf(code) };
    }

    return {
        airports: airportData,
        routes: [...routes.values()].map(({ a, b, counts }) => ({
            a,
            b,
            ab: counts[a], // flights a -> b
            ba: counts[b] // flights b -> a
        }))
    };
}

export function loadTravels() {
    const countries = resolveCountries(travels.countries);
    const states = resolveStates(travels.states);
    const { airports: airportData, routes } = resolveFlights(travels.flights);
    return {
        countries,
        states,
        airports: airportData,
        routes,
        countryCount: countries.length,
        stateCount: states.filter((id) => id !== STATES.DC).length,
        totalCountries: TOTAL_COUNTRIES,
        totalStates: TOTAL_STATES
    };
}
