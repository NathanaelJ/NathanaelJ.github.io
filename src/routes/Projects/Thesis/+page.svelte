<script>
    import { base } from '$app/paths';
    const today = new Date().toLocaleDateString();
</script>

<svelte:head>
  <title>Masters Thesis | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up liquid-glass">
          <h1>Masters Thesis</h1>
      <!-- </div>
      
      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.2s;"> -->
          <p>For my masters' thesis, I developed a physics-based model for the 'swept-stroke' phase of lightning strikes on aircraft under the supervision of Prof. Guerra-Garcia in the <a href="apg.mit.edu">MIT Aerospace Plasma Group.</a> I am continuing the research for my <a href="{base}/Projects/PhD">PhD</a>.<br/><br/></p>
          <a href="{base}/Projects/FYPResources/NJenkins Thesis Final.pdf" class="project-link" download>Download PDF</a>
      </div>
      
      <div class="pdf-container project-section fade-in-up liquid-glass" style="animation-delay: 0.4s;">
          <!-- <div class="pdf-container"> -->
        <iframe class="pdf-viewer" title="Thesis" src="{base}/Projects/FYPResources/NJenkins Thesis Final.pdf"></iframe>
          <!-- </div> -->
      </div>

      <div class="citation-section fade-in-up liquid-glass" style="animation-delay: 0.8s;">
          <p>Please cite this project:</p>
          <p>Jenkins, N. (2023). <i>Numerical Simulation of the Lightning Swept Stroke for
              the Zoning of Unconventional Aircraft.</i> [Master's Thesis.] Boston: Massachusetts Institute of Technology. Available at: http://nathanaelj.github.io/Projects/FYP [Accessed: {today}]</p>
      </div>
  </div>
</main>