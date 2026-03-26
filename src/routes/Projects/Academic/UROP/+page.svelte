<script>
  import { base } from '$app/paths';
  const today = new Date().toLocaleDateString();
</script>

<svelte:head>
  <title>GPU Parallelisation of 2D Navier-Stokes Solver | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up liquid-glass">
          <h1>GPU Parallelisation of a 2D Navier-Stokes Solver</h1>

          <p>Under the supervision of <a href="https://www.turbulencesimulation.com" target="_blank" rel="noreferrer noopener">Sylvain Laizet</a>, I evaluated the performance of <a href="https://github.com/illuhad/hipSYCL" target="_blank" rel="noreferrer noopener">hipSYCL</a>, a high-performance heterogeneous computing framework. Read the full report below.<br/><br/></p>
          <a href="{base}/Projects/AcademicResources/UROP_Report.pdf" class="project-link" download>Download PDF</a>
        </div>

        <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.2s;">
          <div class="pdf-container" style="margin-bottom: 0px; margin-top: 0px;">
              <iframe class="pdf-viewer" title="UROP Report" src="{base}/Projects/AcademicResources/UROP_Report.pdf"></iframe>
          </div>
        </div>

      <div class="citation-section fade-in-up liquid-glass" style="animation-delay: 0.8s;">
        <p>Please cite this project:</p>
        <p>Jenkins, N. (2021). <i>GPU Parallelisation of a 2D Navier-Stokes Solver</i> [pdf] London: Imperial College London. Available at: http://nathanaelj.github.io/Projects/AcademicResources/UROP_Report.pdf [Accessed: {today}]</p>
      </div>
  </div>
</main>
