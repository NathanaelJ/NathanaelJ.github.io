<script>
    import { onMount } from 'svelte';
    import { base } from '$app/paths';
    import { strike } from '$lib/lightning/index.js';

    let portrait;

    // One strike on the portrait per visit (skipped for people who prefer reduced motion)
    onMount(() => {
        const reduced = window.matchMedia('(prefers-reduced-motion: reduce)').matches;
        let seen = false;
        try {
            seen = sessionStorage.getItem('struck') === '1';
            sessionStorage.setItem('struck', '1');
        } catch {
            /* storage unavailable: strike anyway */
        }
        if (reduced || seen) return;
        const timer = setTimeout(() => strike(portrait), 900);
        return () => clearTimeout(timer);
    });
</script>

<svelte:head>
  <title>Nathanael Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="intro-container " style="margin-top: 0;">
        <img
            bind:this={portrait}
            src="/resources-General/Self.jpg"
            class="introimg strikeable"
            alt="Nathanael Jenkins portrait"
            on:click={() => strike(portrait)}
        >
        <div class="intro-text">
            <h1>Hi there!</h1>
            <p>I'm Nathanael, a PhD candidate in Aeronautics and Astronautics at the <a href="https://www.mit.edu" target="_blank" rel="noreferrer noopener">Massachusetts Institute of Technology</a>. Welcome to my little space on the web.</p>
            <div class="intro-buttons">
                <a href="{base}/Projects/PhD" class="apple-button">What I do</a>
                <a href="{base}/Projects/Travels" class="apple-button">Where I've been</a>
            </div>
        </div>
    </div>

    <!-- <div class="intro-container " style="animation-delay: 0.2s;">
        <div class="intro-text">
            <p>I'm researching multi-physics simulations for aircraft lightning protection. Find out more <a href="{base}/Projects/PhD">here</a>.</p>
        </div>
        <figure>
            <img src="/resources-General/CFD_Dark.gif" class="introimg" alt="Animated Taylor-Green vortex">
            <figcaption>DNS of a Taylor-Green vortex using <a href="https://www.incompact3d.com" target="_blank" rel="noopener">Incompact3D</a></figcaption>
        </figure>
    </div> -->

    <div style="text-align: center; margin: var(--spacing-16) 0;">
        <p style="margin-bottom: var(--spacing-6);">Feel free to reach out.</p>
        <a href="mailto:naj20@mit.edu" class="apple-button" style="text-decoration: none;">naj20@mit.edu</a>
    </div>
</main>

