<script>
    import projects from "$lib/projects.json";
    import ProjectCard from "$lib/ProjectCard.svelte";

    $: filteredByYear = projects;

</script>

<svelte:head>
  <title>Projects | N Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="wrapper">
        <div class="page-header fade-in-up">
            <h1>Portfolio</h1>
            <p>Explore my recent projects and research work.</p>
        </div>

        <div class="projects-grid">
        {#each filteredByYear as p}
            <ProjectCard data={p} />
        {/each}
        </div>
    </div>
</main>

