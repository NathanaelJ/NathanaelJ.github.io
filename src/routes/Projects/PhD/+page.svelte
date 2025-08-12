<script>
    import { base } from '$app/paths';
    const today = new Date().toLocaleDateString();
</script>

<svelte:head>
  <title>PhD Research | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up liquid-glass">
          <h1>PhD Research</h1>

          <p>I'm developing computer simulations of lightning strikes on aircraft with a focus on rotorcraft (helicopters and their cousins). This page will be updated with more information as soon as I get around to writing it...<br/><br/> <!-- LINK TO MASTERS PROJECT HERE -->
          </p>
      </div>

      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.6s;">
          <h3>Conferences and Publications</h3>

          <p>▸ Jenkins N, Michael L, Westin B, Guerra-Garcia C. Jul 2025. <b>Mapping of Swept Stroke Physical-Quantities to Zoning Diagrams.</b> EUROCAE WG-31 <a href="https://www.eurocae.net/aircraft-lightning-zoning-workshop/" target="_blank" rel="noreferrer noopener">Zoning Workshop</a>. Paris, France.</p>

          <p>▸ Jenkins N A, Guerra-Garcia C. Dec 2024. <b>Numerical Simulation of the Lightning Swept Stroke: Application to the Results from the NASA Storm Hazards Program.</b> IEEE Access, Vol 12. DOI: <a href="https://doi.org/10.1109/ACCESS.2024.3515833" target="_blank" rel="noreferrer noopener">10.1109/ACCESS.2024.3515833</a></p>

          <p>▸ Austin S, Jenkins N, Guerra-Garcia C, Peraire J, Nguyen NC. Oct 2024. <b>Development and Validation of Numerical Models for Lightning Zoning Assessment.</b> <a href="https://standardsworks.sae.org/standards-committees/ae-2-lightning-committee" target="_blank" rel="noreferrer noopener">SAE AE-2</a> Committee Meeting. Cape Canaveral, Florida.</p>

          <p>▸ Jenkins N, Guerra-Garcia C. Sep 2024. <b>Physics-Based Zoning of Unconventional Aircraft: The Swept Stroke Phase.</b> <a href="https://icolse2024.fee.unicamp.br" target="_blank" rel="noreferrer noopener">International Conference On Lightning and Static Electricity (ICOLSE).</a> Campinas, Brazil. <a href="https://zenodo.org/records/13838314" target="_blank" rel="noreferrer noopener">zenodo.org/records/13838314</a></p>
      </div>

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