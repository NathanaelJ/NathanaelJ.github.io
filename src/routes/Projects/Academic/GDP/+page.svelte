<script>
  import { base } from '$app/paths';
  const today = new Date().toLocaleDateString();
</script>

<svelte:head>
  <title>Hypersonic CFD - Group Design Project | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up liquid-glass">
          <h1>Hypersonic Computational Fluid Dynamics</h1>
          
          <p>For my 3rd year 'Group Design Project', I was tasked with performing an aerodynamic analysis on rocket nosecone designs. Read the full report below.<br/><br/></p>
          <a href="{base}/Projects/AcademicResources/GDP_Report.pdf" class="project-link" download>Download PDF</a>
          
          <p><br/>I also used <a href="https://www.blender.org" target="_blank" rel="noreferrer noopener">Blender</a> and <a href="https://www.blackmagicdesign.com/products/davinciresolve" target="_blank" rel="noreferrer noopener">Davinci Resolve</a> to create a short animation for our group presentations.</p>

          <div class="video-container" style="margin-bottom: 0px;">
            <!-- svelte-ignore a11y-media-has-caption -->
            <figure>
                <video controls>
                    <source src="{base}/Projects/AcademicResources/FAD_Video.mp4" type="video/mp4">
                    Sorry! I upload my videos as mp4... it looks like your browser can't handle that.
                </video>
                <figcaption>Group Design Project Video</figcaption>
            </figure>
          </div>
      </div>
      
      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.4s;">          
          <div class="pdf-container">
              <iframe class="pdf-viewer" title="Group Design Project Report" src="{base}/Projects/AcademicResources/GDP_Report.pdf"></iframe>
          </div>
      </div>
      <div class="citation-section fade-in-up liquid-glass" style="animation-delay: 0.8s;">
        <p>Please cite this project:</p>
        <p>Jenkins, N. (2023). <i>SpaceHAVEN: Aerothermodynamic Analysis of a Hypersonic Rocket Nosecone.</i> [pdf] London: Imperial College London. Available at: http://nathanaelj.github.io/Projects/AcademicResources/GDP_Report.pdf [Accessed: {today}]</p>
      </div>
  </div>
</main>
