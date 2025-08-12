<script>
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
      
      <p>TEXT GOES HERE.<br/><br/></p>
      
      <p>I'm often frustrated by high download costs for seemingly simple CAD models so want to make these models available for hobbyists for free. For commercial use, please <a href="mailto:naj20@mit.edu">contact me</a> first.<br/><br/></p>
      
      <p>
        {#each aircraft as plane}
          <a href="#{plane.id}">{plane.name}</a><br/>
        {/each}
        <a href="#F-106B">F-106B Delta Dart</a>
      </p>
    </div>
    
    {#each aircraft as plane, index}
      <AircraftModel
        aircraft={plane} 
        animationDelay="{(index + 1) * 0.2 + 0.4}s"
      />
    {/each}

    {#each deltaDart as dart, index}
      <MissileModel 
        missile={dart}
        animationDelay="{0.2}s"
      />
    {/each}
  </div>
</main>