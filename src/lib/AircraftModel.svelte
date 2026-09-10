<script>
  import { base } from '$app/paths';
  export let aircraft;
  export let animationDelay = "0s";
</script>

<div class="aircraft-card " style="animation-delay: {animationDelay};">
  <div class="image-container ">
    <img src='{base}/Projects/{aircraft.image}' alt="{aircraft.alt}">
  </div>
  
  <div class="card-content">
    <h3 id="{aircraft.id}">{aircraft.name}</h3>
    
    {#if aircraft.description}
      <p>{aircraft.description}</p>
    {/if}
    
    <div class="download-buttons">
      <a href="{aircraft.link}" target="_blank" class="download-btn ">⇱ OpenVSP</a>
      <a href="{aircraft.downloads.stp}" download class="download-btn ">Download STP</a>
      <a href="{aircraft.downloads.stl}" download class="download-btn ">Download STL</a>
      <a href="{aircraft.downloads.obj}" download class="download-btn ">Download OBJ</a>
    </div>
  </div>
</div>
