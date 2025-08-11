<script>
    const today = new Date().toLocaleDateString();
</script>

<svelte:head>
  <title>Masters Thesis | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <div class="page-header fade-in-up liquid-glass">
          <h1>Masters' Thesis</h1>
          <h2>Numerical simulation of the lightning swept stroke for zoning unconventional aircraft.</h2>
      </div>
      
      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.2s;">
          <p>For my masters' thesis, I developed a physics-based model for the 'swept-stroke' phase of lightning strikes on aircraft under the supervision of Prof. Guerra-Garcia in the <a href="apg.mit.edu">MIT Aerospace Plasma Group.</a> The work is summarised in my master's thesis and published in several papers which will be linked below as they are released publicly.</p>
      </div>
      
      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.4s;">
          <div class="pdf-container">
              <iframe class="pdf-viewer" title="Thesis" src="FYPResources/NJenkins Thesis Final.pdf"></iframe>
          </div>
      </div>

      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.6s;">
          <h3>Publications and Presentations</h3>

          <p>▸ <a href="FYPResources/NJenkins Thesis Final.pdf">Click here to download my master's thesis.</a></p>

          <p>▸ This work was presented at the <a href="https://icolse2024.fee.unicamp.br" target="_blank" rel="noreferrer noopener">International Conference On Lightning and Static Electricity (ICOLSE)</a> in Campinas, Brazil in September 2024. The associated paper is available at <a href="https://zenodo.org/records/13838314" target="_blank" rel="noreferrer noopener">zenodo.org/records/13838314</a></p>

          <p>▸ This work was presented at the SAE AE-2 Comittee Meeting in Cape Canaveral, Florida in October 2024.</p>

          <p>▸ Jenkins N A, Guerra-Garcia C. Numerical Simulation of the Lightning Swept Stroke: Application to the Results from the NASA Storm Hazards Program. IEEE Access. (Early Access) December 2024. DOI: <a href="https://doi.org/10.1109/ACCESS.2024.3515833" target="_blank" rel="noreferrer noopener">10.1109/ACCESS.2024.3515833</a></p>

          <p>More publications related to this work are currently under review and will be released soon.</p>
      </div>

      <div class="citation-section fade-in-up liquid-glass" style="animation-delay: 0.8s;">
          <p>Please cite this project:</p>
          <p>Jenkins, N. (2023). <i>Numerical Simulation of the Lightning Swept Stroke for
              the Zoning of Unconventional Aircraft.</i> [Master's Thesis.] Boston: Massachusetts Institute of Technology. Available at: http://nathanaelj.github.io/Projects/FYP [Accessed: {today}]</p>
      </div>
  </div>
</main>