<script>
  import { base } from '$app/paths';
  export let missile;
  export let animationDelay = "0s";
</script>

<div class="project-section  " style="animation-delay: {animationDelay};">
  <h3 id="{missile.id}">{missile.name}</h3>
  
  {#if missile.description}
    <p>{@html missile.description}</p>
  {/if}
  
  <div class="download-buttons">
    <a href="{missile.downloads.step}" download class="download-btn ">Download STEP</a>
    <a href="{missile.downloads.stl}" download class="download-btn ">Download STL (Binary)</a>
    <a href="{missile.downloads.obj}" download class="download-btn ">Download OBJ</a>
    <a href="{missile.downloads.pdf}" download class="download-btn ">Download drawing (PDF)</a>
  </div>
  
  <div class="image-container ">
    <img src='{base}/Projects/{missile.image}' alt="{missile.alt}">
  </div>
</div>
