<script>
  import { base } from '$app/paths';
  const today = new Date().toLocaleDateString();
</script>

<svelte:head>
  <title>SnoozeSpiral | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up liquid-glass">
          <h1>Data Visualization: Snooze Spiral</h1>

          <p>This is a final project from <a href="https://cs-271.github.io" target="_blank" rel="noreferrer noopener">CS271: Topics in Data Visualization</a> at Harvard University, that I produced in collaboration with <a href="https://www.tejaswi.net" target="_blank" rel="noreferrer noopener">Tejaswi Polimetla</a>.<br/></p>
          <div class="citation-section">
            <p>Please cite this project:</p>
            <p>Polimetla, T. and Jenkins, N. (2026). <i>Snooze Spiral: A Visualization for Cyclical Sleep Tracking</i> [pdf] Harvard University. Cambridge, USA. Available at: http://nathanaelj.github.io/Projects/AcademicResources/SnoozeSpiral.pdf [Accessed: {today}]</p>
          </div>
          <a href="{base}/Projects/AcademicResources/SnoozeSpiral.pdf" class="project-link" download>Download PDF</a> <a href="https://nathanaelj.github.io/SnoozeSpiral" class="project-link" target="_blank" rel="noreferrer noopener">View Demo ⇱</a>
        </div>

        <div class="pdf-container">
            <iframe class="pdf-viewer" title="Snooze Spiral paper" src="{base}/Projects/AcademicResources/SnoozeSpiral.pdf"></iframe>
        </div>
  </div>
</main>
