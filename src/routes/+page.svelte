<script>
    import { base } from '$app/paths';
</script>

<svelte:head>
  <title>Nathanael Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="intro-container fade-in-up">
        <img src="/resources-General/Self.jpg" class="introimg" alt="Nathanael Jenkins portrait">
        <div class="intro-text">
            <h1>Hi there!</h1>
            <p>I'm Nathanael, a PhD student in Aeronautics and Astronautics at the <a href="https://www.mit.edu" target="_blank" rel="noreferrer noopener">Massachusetts Institute of Technology</a>. Welcome to my little space on the web.</p>
        </div>
    </div>

    <div class="intro-container fade-in-up" style="animation-delay: 0.2s;">
        <div class="intro-text">
            <p>I specialize in physics simulations and my current research explores simulation tools for aircraft lightning protection. You can find out more about my projects <a href="{base}/Projects">here</a>.</p>
        </div>
        <figure>
            <img src="/resources-General/CFD_Dark.gif" class="introimg" alt="Animated Taylor-Green vortex">
            <figcaption>DNS of a Taylor-Green vortex using <a href="https://www.incompact3d.com" target="_blank" rel="noreferrer noopener">Incompact3D</a></figcaption>
        </figure>
    </div>
    
    <!-- Additional glass card for research focus -->
    <div class="glass-card research-focus fade-in-up" style="animation-delay: 0.4s;">
        <div class="wrapper">
            <h2>Research Focus</h2>
            <div class="research-grid">
                <div class="research-item">
                    <h3>Computational Fluid Dynamics</h3>
                    <p>High-fidelity simulations for aerospace applications</p>
                </div>
                <div class="research-item">
                    <h3>Lightning Protection</h3>
                    <p>Advanced modeling techniques for aircraft safety</p>
                </div>
                <div class="research-item">
                    <h3>Numerical Methods</h3>
                    <p>Development of efficient computational algorithms</p>
                </div>
            </div>
        </div>
    </div>
</main>

