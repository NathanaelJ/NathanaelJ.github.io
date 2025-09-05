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

          <p>I'm developing computer simulations of lightning strikes on aircraft with a focus on rotorcraft (helicopters, eVTOLs, etc.). On average, one aircraft is struck by lightning every 20 minutes. Now that aircraft designers are breaking the mold of traditional 'tube and wing' aircraft, lightning protection is becoming more complex. <b>This project is working towards an improved understanding of aircraft-lightning physics, and the development of reliable engineering methods for protecting aircraft of the future from lightning hazards.</b><br/>
          </p>
      </div>

      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.6s;">
        <h3>Aircraft Lightning Strikes</h3>

        <p>About 90% of aircraft lightning strikes are initiated by the aircraft. The lightning channel grows from sharp protrusions on the aircraft until it reaches clouds and the ground, at which point a powerful 'return stroke' occurs. In less than a millisecond, the high current in the return stroke heats the lightning channel to more than 30,000ºc (hotter than the surface of the sun)! The sudden heating makes the air expand, making the sound of thunder. The aircraft continues to fly through the lightning channel, which is swept along the surface, in a phenomenon known as the swept stroke. Additional return strokes occur during the swept stroke, leaving a distinctive pattern of damage over the aircraft surface.</p>
        <div class="image-container liquid-glass">
          <img src="{base}/Projects/PhDResources/Strike_Mech.png" alt="Aircraft Lightning Strike Mechanism">
        </div>

        <p>Lightning strikes cause two kinds of damage to aircraft: (1) direct effects, and (2) indirect effects. Direct effects are caused by the intense heat and pressure of the lightning channel which can burn holes in the aircraft surface, ignite flammable materials, and has even been known to vaporise internal wiring. Indirect effects are caused by the intense electromagnetic fields around a lightning channel, which can disable or even destroy internal electronics. Lightning protection systems must prevent both kinds of damage.</p>

        <p>Rotorcraft are particularly vulnerable to lightning strikes, and particularly difficult to protect. A single lightning strike has been known to damage to all 5 rotor blades of a helicopter. Our research is working to better understand where damage is most likely to occur on these complex aircraft geometries.</p>
      </div>

      <div class="project-section fade-in-up liquid-glass" style="animation-delay: 0.6s;">
        <h3>Research Progress</h3>

        <p>As of 2025, we have developed computational methods for simulating the initiation and swept stroke phases of lightning strikes. Our simulation tools produce zoning diagrams which are the industry standard for deciding which components of an aircraft are the most (and least) vulnerable to lightning strikes. This allows engineers to safely optimize the lightning protection system so that it is safe, but not excessive. The process is visualized in the diagram below.</p>

        <div class="image-container liquid-glass">
          <img src="{base}/Projects/PhDResources/Workflow_Ani.gif" alt="Simulation-Based Zoning Workflow">
        </div>

        <p>Watch this space for future updates...</p>
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