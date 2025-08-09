<script>
    import * as d3 from 'd3';

    let arcGenerator = d3.arc().innerRadius(0).outerRadius(50);

    export let data = [];

    let arcData;
    let arcs;
    $: {
        let sliceGenerator = d3.pie().value(d => d.value);
        arcData = sliceGenerator(data);
        arcs = arcData.map(d => arcGenerator(d));
    }

    let colors = d3.scaleOrdinal(d3.schemeTableau10);

    export let selectedIndex = -1;

    let liveText = "";
    function toggleWedge (index, event) {
        if (!event.key || event.key === "Enter") {
            selectedIndex = index;
            const d = data[index];
            liveText = `${d.label}: ${d.value} projects selected.`;
        }
    }

    $: description = `A pie chart showing project counts by year. ${data.map(d => `${d.label}: ${d.value} projects`).join(', ')}.`;

    let showChart = true;
    let tableElement;

    function toggleView() {
        showChart = !showChart;
        liveText = showChart ? "Pie chart view shown." : "Table view shown.";
        if (!showChart) {
            setTimeout(() => tableElement?.focus(), 0);
        }
    }



</script>

<button 
  on:click={toggleView}
  aria-pressed={!showChart}
  aria-label="Toggle between pie chart and table view"
  class="toggle-button">
    {showChart ? 'Show Table' : 'Show Chart'}
</button>

{#if showChart}
<div class="pie-container">
    <svg viewBox="-50 -50 100 100"
        role="img" 
        aria-labelledby="pie-title pie-desc">
        <title id="pie-title">Projects by Year</title>
        <desc id="pie-desc">{description}</desc>
        <circle class="pie-outline" r="50" />
        {#each arcs as arc, index}
            <path d={arc} fill={colors(index)}
                class:selected={selectedIndex === index}
                on:click={e => toggleWedge(index, e)}
                on:keyup={e => toggleWedge(index, e)} 
                tabindex="0"
                role="button"
                aria-label={`Wedge for ${data[index].label}: ${data[index].value} projects`} />
        {/each}
    </svg>
    <p aria-live="polite" class="sr-only">{liveText}</p>

    <ul class="legend">
        {#each data as d, index}
            <li style="--color: { colors(index) }" class:selected={selectedIndex === index}>
                <button
                    on:click={e => selectedIndex = selectedIndex === index ? -1 : index}
                    on:keyup={e => selectedIndex = selectedIndex === index ? -1 : index}
                    aria-label={`Legend item: ${d.label}: ${d.value} projects`}
                    class="legend-button">
                    <span class="swatch"></span>
                    {d.label} <em>({d.value})</em>
                </button>
            </li>
        {/each}
    </ul>
</div>
{/if}

{#if !showChart}
<table bind:this={tableElement} aria-label="Table showing project counts by year" class="data-table" tabindex="-1">
    <caption>Projects by Year</caption>
    <thead>
        <tr>
          <th id="year-header" scope="col">Year</th>
          <th id="projects-header" scope="col">Projects</th>
        </tr>
      </thead>      
    <tbody>
        {#each data as d, i}
          <tr>
            <th id="row-{i}" scope="row">{d.label}</th>
            <td aria-labelledby="row-{i} projects-header">{d.value}</td>
          </tr>
        {/each}
      </tbody>
  </table>
{/if}


<style>
    svg {
        max-width: 20em;
        margin-block: 2em;

        /* Do not clip shapes outside the viewBox */
        overflow: visible;
    }

    .swatch {
        display: inline-block;
        width: 1em;
        height: 1em;
        background-color: var(--color);
        border-radius: 20%;
        margin-right: 0.5em;
    }

    .legend {
        list-style: none;
        padding: 0;
        margin: 0;
        margin-left: 2em;
        flex: 1;

        display: grid;
        grid-template-columns: repeat(auto-fill, minmax(8em, 1fr));
        gap: 1em;

        border: 1px solid var(--color-border);
        border-radius: 0.5em;
        height: 100%;
        padding: 1em;
    }

    .selected {
        --color: oklch(60% 45% 0) !important;
        
        &:is(path) {
            fill: var(--color) !important;
        }
        
        &:is(li) {
            color: var(--color);
        }
    }
    path:not(.selected) {
        opacity: 50%;
    }

    path:focus-visible,
    path:hover {
        opacity: 100% !important;
        stroke: white;
        stroke-width: 2px;
        stroke-dasharray: 4;
    }

    ul:has(.selected) li:not(.selected) {
        color: gray;
    }

    li {
        display: flex;
        align-items: center;
        gap: 0.5em;
    }

    .pie-container {
        display: flex;
        align-items: center;
        justify-content: center;
    }

    path {
        transition: 300ms;
        cursor: pointer;
        outline: none;
    }

    .legend-button {
        display: flex;
        align-items: center;
        gap: 0.5em;
        background: none;
        border: none;
        padding: 0;
        color: inherit;
        cursor: pointer;
        width: 100%;
        text-align: left;
    }

    .sr-only {
        position: absolute;
        left: -9999px;
        width: 1px;
        height: 1px;
        overflow: hidden;
    }



    .data-table {
    margin-top: 1rem;
    margin-bottom: 1rem;
    border-collapse: collapse;
    width: 100%;
    max-width: 30em;
    }

    .data-table caption {
    font-weight: bold;
    margin-bottom: 0.5em;
    text-align: left;
    }

    .data-table th,
    .data-table td {
    border: 1px solid #ccc;
    padding: 0.5em;
    text-align: left;
    }

    .data-table th {
    background-color: #f0f0f0;
    }

    .pie-outline {
        stroke: black;
        fill: none;
        stroke-width: 1;
    }

    path:focus-visible {
    stroke: white;
    stroke-width: 2px;
    stroke-dasharray: 4; /* Adjust the dash length as needed */
    }



</style>