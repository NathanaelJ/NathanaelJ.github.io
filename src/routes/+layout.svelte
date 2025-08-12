<script>
    import { base } from '$app/paths';
    import { page } from "$app/stores";
    import projects from '$lib/projects.json';

    $: routeId = $page?.route?.id || '';
</script>

<svelte:head>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Roboto+Serif:ital,opsz,wght@0,8..144,100..900;1,8..144,100..900&display=swap');
    </style>
</svelte:head>

<header class="site-header">
    <div class="wrapper">
        <div class="title-block">
            <a href="{base}/." class="name">Nathanael Jenkins</a>
        </div>
        
        <nav class="menu-right">
            <a href="{base}/." class="menu-links" class:current-page={routeId === "/"} id="home-link">Home</a>
            
            <div class="dropdown">
                <a class="menu-links" href="{base}/Projects" class:current-page={routeId.includes("/Projects") || routeId.includes("dataviz")} id="projects-link">Projects</a>
                <div class="dropdown-content">
                    {#each projects.filter(project => project.dropdown) as project}
                        <a href="{base}/{project.link}" id="{project.title.toLowerCase().replace(/\s+/g, '-')}-link">{project.button_title}</a>
                    {/each}
                </div>
            </div>
            <a href="{base}/resume" class="menu-links" class:current-page={routeId.includes("/resume")} id="resume-link">Resume</a>
        </nav>
    </div>
    <hr class="rule">
</header>

<slot></slot>

<footer class="footer">
    <hr class="rule">

    <nav class="social-links-container">
        <a class="social-links" href="https://www.linkedin.com/in/n-jenkins/" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/In.png" alt="LinkedIn"/> LinkedIn</a>
        <a class="social-links" href="https://github.com/NathanaelJ" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/Git.png" alt="GitHub"/> GitHub</a>
    </nav>

    <div class="footer-right">
        <p>&copy; Nathanael Jenkins, 2025</p>
        <p>improved using <a href="https://cursor.com/" target="_blank" rel="noreferrer noopener">Cursor</a></p>
    </div>
</footer>