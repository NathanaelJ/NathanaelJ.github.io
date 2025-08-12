<script>
  export let aircraft;
  export let animationDelay = "0s";
</script>

<div class="project-section fade-in-up liquid-glass" style="animation-delay: {animationDelay};">
  <h3 id="{aircraft.id}">{aircraft.name}</h3>
  
  {#if aircraft.description}
    <p>{aircraft.description}</p>
  {/if}
  
  <div class="download-buttons">
    <a href="{aircraft.downloads.step}" download class="download-btn liquid-glass">Download STEP</a>
    <a href="{aircraft.downloads.stl}" download class="download-btn liquid-glass">Download STL (Binary)</a>
    <a href="{aircraft.downloads.obj}" download class="download-btn liquid-glass">Download OBJ</a>
    <a href="{aircraft.downloads.pdf}" download class="download-btn liquid-glass">Download drawing (PDF)</a>
  </div>
  
  <div class="image-container liquid-glass">
    <img src="{aircraft.image}" alt="{aircraft.alt}">
  </div>
</div>
