<script>
    import { base } from '$app/paths';
</script>

<svelte:head>
  <title>Nathanael Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="intro-container fade-in-up" style="margin-top: 0;">
        <img src="/resources-General/Self.jpg" class="introimg" alt="Nathanael Jenkins portrait">
        <div class="intro-text">
            <h1>Hi there!</h1>
            <p>I'm Nathanael, a PhD student in Aeronautics and Astronautics at the <a href="https://www.mit.edu" target="_blank" rel="noreferrer noopener">Massachusetts Institute of Technology</a>. Welcome to my little space on the web.</p>
        </div>
    </div>

    <div class="intro-container fade-in-up" style="animation-delay: 0.2s;">
        <div class="intro-text">
            <p>I specialize in physics simulations and my current research explores simulation tools for aircraft lightning protection. You can find out more about my research <a href="{base}/Projects/Thesis">here</a>.</p>
        </div>
        <figure>
            <img src="/resources-General/CFD_Dark.gif" class="introimg" alt="Animated Taylor-Green vortex">
            <figcaption>DNS of a Taylor-Green vortex using <a href="https://www.incompact3d.com" target="_blank" rel="noopener">Incompact3D</a></figcaption>
        </figure>
    </div>

    <div style="text-align: center; margin: var(--spacing-16) 0;">
        <p style="margin-bottom: var(--spacing-6);">Feel free to reach out about my research</p>
        <a href="mailto:naj20@mit.edu" class="apple-button">naj20@mit.edu</a>
    </div>
</main>

