<script>
  import ProjectCard from "$lib/ProjectCard.svelte";
  import projects from "$lib/projects.json";

  // Filter to only show academic projects
  $: academicProjects = projects.filter(project => 
    project.link.includes("/Academic/")
  );
</script>

<svelte:head>
  <title>Academic Projects | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up">
          <h1>Academic Projects</h1>
          <p>A collection of projects from my undergraduate and pre-university studies</p>
      </div>

      <div class="projects-grid">
          {#each academicProjects as project}
              <ProjectCard data={project} />
          {/each}
      </div>
  </div>
</main>