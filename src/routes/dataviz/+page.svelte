<script>
    import vizProjects from "$lib/vizProjects.json";
    import ProjectCard from "$lib/ProjectCard.svelte";
</script>

<svelte:head>
  <title>6.C85 Portfolio | N Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="wrapper">
        <h1>6.C85: Interactive Data Visualisation and Society</h1>
        <p>This portfolio contains my class work from an MIT class on data visualization and society.</p>

        <div class="projects-grid">
            {#each vizProjects as p}
                <ProjectCard data={p} />
            {/each}

            <article class="project-card">
                <img src="/Thumbnails/PLACEHOLDER.jpeg" alt="Project thumbnail" class="project-image">
                <div class="project-content">
                    <h2>More coming soon...</h2>
                </div>
            </article>
        </div>
    </div>
</main>

<style>
    /* Project card item */
    .project-card {
        background: var(--color-background);
        border-radius: 8px;
        overflow: hidden;
        transition: transform 0.2s;
        box-shadow: 0 2px 5px var(--color-border);
    }
    .project-card:hover {
        transform: translateY(-5px);
    }
</style>