<script>
  export let missile;
  export let animationDelay = "0s";
</script>

<div class="project-section fade-in-up liquid-glass" style="animation-delay: {animationDelay};">
  <h3 id="{missile.id}">{missile.name}</h3>
  
  {#if missile.description}
    <p>{@html missile.description}</p>
  {/if}
  
  <div class="download-buttons">
    <a href="{missile.downloads.step}" download class="download-btn liquid-glass">Download STEP</a>
    <a href="{missile.downloads.stl}" download class="download-btn liquid-glass">Download STL (Binary)</a>
    <a href="{missile.downloads.obj}" download class="download-btn liquid-glass">Download OBJ</a>
    <a href="{missile.downloads.pdf}" download class="download-btn liquid-glass">Download drawing (PDF)</a>
  </div>
  
  <div class="image-container liquid-glass">
    <img src="{missile.image}" alt="{missile.alt}">
  </div>
</div>
