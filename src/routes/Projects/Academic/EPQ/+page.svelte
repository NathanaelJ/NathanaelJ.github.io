<script>
  import { base } from '$app/paths';
  const today = new Date().toLocaleDateString();
</script>

<svelte:head>
  <title>Ion Propulsion - Extended Project Qualification | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up liquid-glass">
          <h1>Ion Propulsion</h1>

          <p>Alongside A-Level studies, I conducted an 'Extended Project Qualification' (EPQ) exploring ion propulsion for air and space travel. While ion propulsion is popular on unmanned spacecraft, it has not yet been made viable for atmospheric vehicles as it cannot generate high magnitudes of thrust. Read the full report below.<br/><br/></p>
          <a href="{base}/Projects/AcademicResources/EPQ.pdf" class="project-link" download>Download PDF</a>
        </div>

          <div class="pdf-container">
              <iframe class="pdf-viewer" title="Extended Project Report" src="{base}/Projects/AcademicResources/EPQ.pdf"></iframe>
          </div>

        <div class="citation-section fade-in-up liquid-glass" style="animation-delay: 0.8s;">
          <p>Please cite this project:</p>
          <p>Jenkins, N. (2019). <i>Is ion propulsion the future of air and space transport?</i> [pdf] Winchester: Peter Symonds College. Available at: http://nathanaelj.github.io/Projects/AcademicResources/EPQ.pdf [Accessed: {today}]</p>
        </div>
  </div>
</main>
