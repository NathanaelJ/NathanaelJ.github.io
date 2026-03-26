<script>
  import { base } from '$app/paths';
  import MissileModel from '$lib/MissileModel.svelte';
  import missiles from '$lib/missiles.json';
</script>

<svelte:head>
  <title>Modelling | N Jenkins</title>
</svelte:head>

<main class="site-main modelling-page">
  <div class="wrapper">
    <div class="page-header fade-in-up liquid-glass">
      <h1>Missile Models</h1>
      
      <p>All of the data relating to these models was taken from publicly available data, predominantly photos published by militaries or manufacturers. Dimensions are approximate.<br/><br/></p>
      
      <p>Free to hobbyists. For commercial use, please <a href="mailto:naj20@mit.edu">contact me</a> first.<br/><br/></p>
      
      <p>
        {#each missiles as missile}
          <a href="#{missile.id}">{missile.name}</a><br/>
        {/each}
      </p>
    </div>
    
    {#each missiles as missile, index}
      <MissileModel 
        {missile} 
        animationDelay="{(index + 1) * 0.2 + 0.4}s"
      />
    {/each}
  </div>
</main>