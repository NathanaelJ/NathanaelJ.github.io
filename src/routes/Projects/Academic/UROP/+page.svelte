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

          <p>Under the supervision of <a href="https://www.turbulencesimulation.com" target="_blank" rel="noreferrer noopener">Sylvain Laizet</a>, I completed a research project exploring parallelism in Computational Fluid Dynamics (CFD). The project evaluated the performance of a framework called <a href="https://github.com/illuhad/hipSYCL" target="_blank" rel="noreferrer noopener">hipSYCL</a>, which is designed to enable high-performance heterogeneous computing (this is a fancy way of saying 'using all of the hardware in a computer at once'). The full project report is shown below, or <a href="{base}/Projects/AcademicResources/UROP_Report.pdf">click to download.</a></p>
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
