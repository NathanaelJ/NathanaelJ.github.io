<script>
    import { base } from '$app/paths';
    const today = new Date().toLocaleDateString();

    import pubs from "$lib/publications.json";
    import ProjectCard from "$lib/ProjectCard.svelte";

    $: filteredByYear = pubs;
</script>

<svelte:head>
  <title>PhD Research | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up liquid-glass">
          <h1>PhD Research</h1>

          <p>On average, an aircraft is struck by lightning somewhere in the world every 20 minutes. This project is working towards an improved understanding of aircraft-lightning physics, and the development of reliable engineering methods for protecting aircraft of the future from lightning hazards.<br/>
          </p>

      </div>

      <div class="project-section">
          <h3>Publications</h3>
      </div>

      <div class="projects-grid">
      {#each filteredByYear as p}
          <ProjectCard data={p} />
      {/each}
      </div>

      <!-- NOTE TO SELF: Add list of presentations too?? -->


      <!-- <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.6s;">
          <h3>Conferences and Publications</h3>

          <p>▸ Jenkins N A, Michael L, Westin B A, Guerra-Garcia C. Oct 2025. <b>A Physics-Based Approach to Aircraft Lightning Zoning: Zone 2</b> IEEE Access, Vol 13. DOI: <a href="https://doi.org/10.1109/ACCESS.2025.3628197" target="_blank" rel="noreferrer noopener">10.1109/ACCESS.2025.3628197</a></p>

          <p>▸ Jenkins N A. Oct 2025. <b>Physical Interpretation of Swept Stroke Data (Supplementary Document)</b> Supplementary to '<i>A Physics-Based Approach to Aircraft Lightning Zoning: Zone 2</i>'. Available at: <a href="https://nathanaelj.github.io/Projects/PhDResources/IEEE_Suppl.pdf" target="_blank" rel="noreferrer noopener">nathanaelj.github.io/Projects/PhDResources/IEEE_Suppl.pdf</a></p>

          <p>▸ Jenkins N, Guerra-Garcia C. Oct 2025. <b>Recent Progress in Zoning by Simulation.</b> <a href="https://standardsworks.sae.org/standards-committees/ae-2-lightning-committee" target="_blank" rel="noreferrer noopener">SAE AE-2</a> Committee Meeting. Pittsburgh, Pennsylvania.</p>

          <p>▸ Jenkins N, Michael L, Westin B, Guerra-Garcia C. Jul 2025. <b>Mapping of Swept Stroke Physical-Quantities to Zoning Diagrams.</b> EUROCAE WG-31 <a href="https://www.eurocae.net/aircraft-lightning-zoning-workshop/" target="_blank" rel="noreferrer noopener">Zoning Workshop</a>. Paris, France.</p>

          <p>▸ Jenkins N A, Guerra-Garcia C. Dec 2024. <b>Numerical Simulation of the Lightning Swept Stroke: Application to the Results from the NASA Storm Hazards Program.</b> IEEE Access, Vol 12. DOI: <a href="https://doi.org/10.1109/ACCESS.2024.3515833" target="_blank" rel="noreferrer noopener">10.1109/ACCESS.2024.3515833</a></p>

          <p>▸ Austin S, Jenkins N, Guerra-Garcia C, Peraire J, Nguyen NC. Oct 2024. <b>Development and Validation of Numerical Models for Lightning Zoning Assessment.</b> <a href="https://standardsworks.sae.org/standards-committees/ae-2-lightning-committee" target="_blank" rel="noreferrer noopener">SAE AE-2</a> Committee Meeting. Cape Canaveral, Florida.</p>

          <p>▸ Jenkins N, Guerra-Garcia C. Sep 2024. <b>Physics-Based Zoning of Unconventional Aircraft: The Swept Stroke Phase.</b> <a href="https://icolse2024.fee.unicamp.br" target="_blank" rel="noreferrer noopener">International Conference On Lightning and Static Electricity (ICOLSE).</a> Campinas, Brazil. <a href="https://zenodo.org/records/13838314" target="_blank" rel="noreferrer noopener">zenodo.org/records/13838314</a></p>
      </div> -->

      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.8s;">
          <h3>Related Links</h3>
          <div class="download-buttons">
            <a href="{base}/Projects/Thesis" target="_blank" rel="noreferrer noopener" class="download-btn liquid-glass">Masters Thesis</a>
            <a href="https://apg.mit.edu" target="_blank" rel="noreferrer noopener" class="download-btn liquid-glass">⇱ Aerospace Plasma Group</a>
            <a href="https://aeroastro.mit.edu/people/carmen-guerra-garcia/" target="_blank" rel="noreferrer noopener" class="download-btn liquid-glass">⇱ Prof. Guerra-Garcia</a>
          </div>
      </div>

      <!-- Add citation once PhD published -->
      <!-- <div class="citation-section fade-in-up liquid-glass" style="animation-delay: 0.8s;">
          <p>Please cite this project:</p>
          <p>Jenkins, N. (2023). <i>Numerical Simulation of the Lightning Swept Stroke for
              the Zoning of Unconventional Aircraft.</i> [Master's Thesis.] Boston: Massachusetts Institute of Technology. Available at: http://nathanaelj.github.io/Projects/FYP [Accessed: {today}]</p>
      </div> -->
  </div>
</main>