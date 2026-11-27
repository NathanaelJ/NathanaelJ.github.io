<script>
    import { base } from '$app/paths';
    import { page } from "$app/stores";
    import projects from '$lib/projects.json';
    import Lightning from '$lib/Lightning.svelte';
    import StormToggle from '$lib/StormToggle.svelte';

    $: routeId = $page?.route?.id || '';
</script>

<svelte:head>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Roboto+Serif:ital,opsz,wght@0,8..144,100..900;1,8..144,100..900&display=swap');
    </style>

    <!-- Google tag (gtag.js) -->
    <script async src="https://www.googletagmanager.com/gtag/js?id=G-PKWKKGM4TW"></script>
    <script>
        window.dataLayer = window.dataLayer || [];
        function gtag(){dataLayer.push(arguments);}
        gtag('js', new Date());
        gtag('config', 'G-PKWKKGM4TW');
    </script>
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
                    <div class="dropdown-label">Recommended</div>
                    {#each projects.filter(project => project.dropdown) as project}
                        <a href="{base}/{project.link}" id="{project.title.toLowerCase().replace(/\s+/g, '-')}-link">{project.button_title}</a>
                    {/each}
                    <a href="{base}/Projects" class="dropdown-view-all">All Projects</a>
                </div>
            </div>
            <a href="{base}/CV" class="menu-links" class:current-page={routeId.includes("/CV")} id="resume-link">CV</a>
            <StormToggle />
            <!-- Secret: the only way in to the hidden /sinks page -->
            <a href="{base}/sinks" class="sink-link" class:current-page={routeId.startsWith("/sinks")} aria-label="Sinks" rel="nofollow">
                <svg viewBox="0 0 24 24" aria-hidden="true">
                    <path d="M9 12V5a2.5 2.5 0 0 1 5 0v1.5" />
                    <path d="M2.5 12h19" />
                    <path d="M4 12a8 8 0 0 0 16 0" />
                </svg>
            </a>
        </nav>
    </div>
    <hr class="rule">
</header>

<slot></slot>

<Lightning />

<footer class="footer">
    <hr class="rule">

    <nav class="social-links-container">
        <a class="social-links" href="https://www.linkedin.com/in/n-jenkins/" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/In.png" alt="LinkedIn"/> LinkedIn</a>
        <a class="social-links" href="https://github.com/NathanaelJ" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/Git.png" alt="GitHub"/> GitHub</a>
        <a class="social-links" href="https://orcid.org/0009-0005-1155-9314" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/Orcid.png" alt="ORCID"/> ORCID</a>
    </nav>

    <div class="footer-right">
        <p>&copy; Nathanael Jenkins, 2026</p>
        <p>improved using <a href="https://cursor.com/" target="_blank" rel="noreferrer noopener">Cursor</a> and <a href="https://claude.com/claude-code" target="_blank" rel="noreferrer noopener">Claude</a></p>
    </div>
</footer>
