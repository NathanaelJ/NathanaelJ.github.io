<script>
    import projects from "$lib/projects.json";
    import ProjectCard from "$lib/ProjectCard.svelte";
    import Pie from '$lib/Pie.svelte';
    import * as d3 from 'd3';

    let query = "";

    $: filteredProjects = projects.filter(project => {
            let values = Object.values(project).join("\n").toLowerCase();
            return values.includes(query.toLowerCase());
        });

    let pieData;

    $: {
        pieData = {}; 

        let rolledData = d3.rollups(filteredProjects, v => v.length, d => d.year);

        pieData = rolledData.map(([year, count]) => {
            return { value: count, label: year };
        });
    }

    let selectedYearIndex = -1;

    let selectedYear;
    $: selectedYear = selectedYearIndex > -1 ? pieData[selectedYearIndex].label : null;

    $: filteredByYear = filteredProjects.filter(project => {
        if (selectedYear) {
            return project.year === selectedYear;
        }

        return true;
    });

</script>

<svelte:head>
  <title>Projects | N Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="wrapper">
        <h1>{ projects.length } Projects</h1>
        <p>Explore my recent projects.</p>

        <Pie data={pieData} bind:selectedIndex={selectedYearIndex} />

        <div class="search-container">
            <span aria-hidden="true" class="emoji">🔍</span>
            <input class="search-input" type="search" bind:value={query} aria-label="Project search bar" placeholder="Search projects…" />
        </div>

        <div class="projects-grid">
        {#each filteredByYear as p}
            <!-- <article class="project-card">
            <img src={p.img} alt="Project Thumbnail" class="project-image"/>
            <div class="project-content">
                <h2>{p.title}</h2>
                <h3>{p.subtitle}</h3>
                <p>{p.description}</p>
                <a href="/dataviz" class="project-link">View Project</a>
            </div>
            </article> -->
            <ProjectCard data={p} />
        {/each}
        </div>
    </div>
</main>

<style>
    .search-input {
        width: 100%;
        padding: 1em;
        border: 1px solid #ccc;
        border-radius: 0.5em;
    }

    .search-container {
        position: relative;
    }

    .emoji {
    position: absolute;
    left: 0.5rem;
    top: 50%;
    transform: translateY(-50%);
    pointer-events: none;
    font-size: 1rem;
    }

    input[type="search"] {
    padding-left: 2rem; /* gives space for the emoji */
    width: 100%;
    }


</style>