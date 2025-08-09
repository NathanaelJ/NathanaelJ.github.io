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
        <h1>{ projects.length } Projects</h1>
        <p>Explore my recent projects.</p>

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

