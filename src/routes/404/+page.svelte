<script>
  import { base } from '$app/paths';
</script>

<svelte:head>
  <title>404: Page Not Found</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
    <div class="error-container fade-in-up">
      <h1>404: Page Not Found</h1>
    </div>

    <div class="intro-container fade-in-up" style="animation-delay: 0.2s;">
      <div class="intro-text">
        <p>Oops! It looks like you've wandered into uncharted territory. While you're here, enjoy this photo of Minnie the dog.</p>
      </div>
      <figure>
        <img src="{base}/Dogs/Minnie.jpeg" alt="Minnie the dog" class="introimg" />
      </figure>
    </div>

    <div class="text-center" style="margin-top: 2em;">
      <a href="{base}/" class="project-link">Return to Homepage</a>
    </div>
  </div>
</main>


