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

          <p>Alongside A-Level studies, I conducted a research project in electric propulsion, exploring the question, 'is ion propulsion the future of space and air travel?'. While ion propulsion currently powers many unmanned spacecraft, it has not yet been made viable for atmospheric vehicles. This is a result of the way in which it generates thrust being extremely efficient but incredibly weak. You can read the detailed report below, or <a href="{base}/Projects/AcademicResources/EPQ.pdf" download>download the report.</a></p>
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
