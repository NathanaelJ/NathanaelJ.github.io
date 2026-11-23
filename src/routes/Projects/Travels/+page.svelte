<script>
    import TravelMap from '$lib/TravelMap.svelte';
    import worldUrl from 'world-atlas/countries-50m.json?url';
    import usUrl from 'us-atlas/states-10m.json?url';

    export let data;
</script>

<svelte:head>
    <title>Travels | N Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="wrapper">
        <div class="page-header">
            <h1 class="visually-hidden">Travels</h1>
            <p>Places I've been, and flights I've taken...</p>
        </div>
    </div>

    <div class="travels">
        <TravelMap
            kind="world"
            topoUrl={worldUrl}
            visited={data.countries}
            routes={data.routes}
            airports={data.airports}
            count={data.countryCount}
            total={data.totalCountries}
            unit="countries"
        />

        <TravelMap
            kind="us"
            topoUrl={usUrl}
            visited={data.states}
            routes={data.routes}
            airports={data.airports}
            count={data.stateCount}
            total={data.totalStates}
            unit="states"
        />
    </div>
</main>

<style>
    .travels {
        max-width: 1280px;
        margin: var(--spacing-4) auto 0;
        padding: 0 var(--spacing-4);
    }

    .travels :global(.travel-map:last-of-type) {
        max-width: 880px;
        margin-left: auto;
        margin-right: auto;
    }
</style>
