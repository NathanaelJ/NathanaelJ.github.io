<script>
    import vizProjects from "$lib/vizProjects.json";
    import ProjectCard from "$lib/ProjectCard.svelte";
</script>

<svelte:head>
  <title>6.C85 Portfolio | N Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="wrapper">
        <div class="page-header fade-in-up">
            <h1>6.C85: Interactive Data Visualisation and Society</h1>
            <p>This contains my class work from the MIT class on <a href="https://vis-society.github.io/final-project/showcase/" target="_blank" rel="noopener">interactive data visualization and society</a> (Fall 2024).</p>
        </div>

        <div class="projects-grid">
            {#each vizProjects as p}
                <ProjectCard data={p} />
            {/each}
        </div>
    </div>
</main>