<script>
  import { base } from '$app/paths';
  import MissileModel from '$lib/MissileModel.svelte';
  import deltaDart from '$lib/F106.json';
  import AircraftModel from '$lib/AircraftModel.svelte';
  import aircraft from '$lib/aircraft.json';
</script>

<svelte:head>
  <title>Aircraft | N Jenkins</title>
</svelte:head>

<main class="site-main modelling-page">
  <div class="wrapper">
    <div class="page-header fade-in-up liquid-glass">
      <h1>Aircraft Models</h1>
      
      <p>I created these concept-level aircraft models to support my <a href="{base}/Projects/PhD">PhD</a> research. They are <b>not</b> representative of any single, existing aircraft, making them easier to publish and share.<br/><br/></p>
      
      <p>
        {#each aircraft as plane}
          <a href="#{plane.id}">{plane.name}</a><br/>
        {/each}
        <a href="#F-106B">F-106B Delta Dart</a>
      </p>
    </div>
    
    <div class="aircraft-grid">
      {#each aircraft as plane, index}
        <AircraftModel
          aircraft={plane} 
          animationDelay="{(index + 1) * 0.2 + 0.4}s"
        />
      {/each}
    </div>

    {#each deltaDart as dart, index}
      <MissileModel 
        missile={dart}
        animationDelay="{0.2}s"
      />
    {/each}
  </div>
</main>