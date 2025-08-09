<script>
    import projects from "$lib/projects.json";
    import ProjectCard from "$lib/ProjectCard.svelte";
    import AircraftFinder from "$lib/AircraftFinder.svelte";
    import { onMount } from "svelte";
    import { base } from '$app/paths';
    import { page } from '$app/stores';

    let githubData = null;
    let loading = true;
    let error = null;

    onMount(async () => {
        try {
            const response = await fetch("https://api.github.com/users/nathanaelj");
            githubData = await response.json();
        } catch (err) {
            error = err;
        }
        loading = false;
    });
</script>

<svelte:head>
  <title>Nathanael Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="intro-container">
        <img src="/resources-General/Self.jpg" class="introimg" alt="Nathanael Jenkins portrait">
        <div class="intro-text">
            <h1>Hi there!</h1>
            <p>I'm Nathanael, a PhD student in Aeronautics and Astronautics at the <a href="https://www.mit.edu" target="_blank" rel="noreferrer noopener">Massachusetts Institute of Technology</a>. Welcome to my little space on the web.</p>
        </div>
    </div>

    <div class="intro-container">
        <div class="intro-text">
            <p>I specialize in physics simulations and my current research explores simulation tools for aircraft lightning protection. You can find out more about my projects <a href="{base}/Projects">here</a>.</p>
        </div>
        <figure>
            <img src="/resources-General/CFD_Dark.gif" class="introimg" alt="Animated Taylor-Green vortex">
            <figcaption>DNS of a Taylor-Green vortex using <a href="https://www.incompact3d.com" target="_blank" rel="noreferrer noopener">Incompact3D</a></figcaption>
        </figure>
    </div>
    <br/>

    <!-- GitHub Stats -->
    {#if loading}
        <p>Loading...</p>
    {:else if error}
        <p class="error">Something went wrong: {error.message}</p>
    {:else}
        <section class="processing-box">
            <a href="https://github.com/nathanaelj" target="_blank" rel="noreferrer noopener" style="font-style: normal; font-family: var(--font-primary); font-size: var(--font-size-xlarge); text-align: center;">GitHub</a>
            <dl>
                <dt>Followers</dt>
                <dt>Following</dt>
                <dt>Public Repos</dt>
                <dd>{githubData.followers}</dd>
                <dd>{githubData.following}</dd>
                <dd>{githubData.public_repos}</dd>
            </dl>
        </section>
    {/if}
    <br/>

    <!-- Find closest aircraft -->
    <!-- Relies on ADSB.LOL API, which may require keys in the future: https://api.adsb.lol/docs#/ -->
    <!-- <AircraftFinder /> -->
    <!-- <br/> -->

    <hr width="50%" size="1px" color="#555" z-index="1">
    <div class="intro-container">
        <div class="intro-text">
        <h1 style="font-style: normal; font-family: var(--font-primary)">Featured Projects</h1>
        <div class="projects-grid">
        {#each projects.slice(0, 3) as p}
            <ProjectCard data={p} />
        {/each}
        </div>
        </div>
    </div>
</main>

<style>
    dl {
        grid-template-columns: repeat(3, 1fr);
    }
</style>