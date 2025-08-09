<script>
    import { base } from '$app/paths';
    import { page } from "$app/stores";
    import { colorScheme, cycleScheme } from '$lib/stores/colorScheme';
    import { onMount } from 'svelte';

    onMount(() => {
        // Listen for system scheme changes when in auto mode
        const mediaQuery = window.matchMedia('(prefers-color-scheme: dark)');
        const handleChange = (e) => {
            if ($colorScheme === 'auto') {
                document.documentElement.removeAttribute('color-scheme');
                if (e.matches) {
                    document.documentElement.setAttribute('color-scheme', 'dark');
                }
            }
        };
        mediaQuery.addEventListener('change', handleChange);
        return () => mediaQuery.removeEventListener('change', handleChange);
    });
</script>

<header class="site-header">
    <div class="wrapper">
        <div class="title-block">
            <a href="{base}/." class="name1">Nathanael </a><a href="{base}/." class="name">Jenkins<br/></a>
            <a href="{base}/dataviz" class="subtitle">6.C85 Lab Portfolio (with Svelte)</a>
        </div>
        
        <nav class="menu-right">
            <a href="{base}/." class="menu-links" class:current-page={$page.route.id === "/"} id="home-link">Home</a>
            <a href="{base}/dataviz" class="menu-links portfolio-only" class:current-page={$page.route.id.includes("/dataviz")} id="portfolio-link">6.C85</a>
            
            <div class="dropdown">
                <a class="menu-links" href="{base}/Projects" class:current-page={$page.route.id.includes("/Projects")} id="projects-link">Projects</a>
                <div class="dropdown-content">
                    <a href="{base}/dataviz" id="dataviz-link">Data Visualization</a>
                    <a href="{base}/Projects/Thesis" id="FYP-link">Thesis</a>
                    <a href="{base}/Projects/Modelling" id="modeling-link">CAD Models</a>
                    <a href="{base}/Projects/ICLR" id="ICLR-link">Rocketry</a>
                    <a href="{base}/Projects/Academic" id="OtherProj-link">Other</a>
                </div>
            </div>
            <a href="{base}/resume" class="menu-links" class:current-page={$page.route.id.includes("/resume")} id="resume-link">Resume</a>
            <a href="{base}/meta" class="menu-links" class:current-page={$page.route.id.includes("/meta")} id="portfolio-link">Meta</a>
        </nav>
    </div>
    <hr class="rule" size="1px">
</header>

<slot></slot>

<footer class="footer">
    <hr class="rule" size="1px">

    <div class="footer-nav-row">
        <nav class="contacts">
            <a class="menu-links" style="border-bottom: none;" href="mailto:naj20@mit.edu">naj20@mit.edu</a>
            <!--<a class="menu-links" href="tel:07960264171">+44(0) 7960 264171</a>-->
        </nav>

        <div class="color-mode-footer">
            <button class="color-mode-button" on:click={cycleScheme} aria-label="Toggle color scheme" title="Toggle color scheme">
                <p>{$colorScheme.charAt(0).toUpperCase() + $colorScheme.slice(1)}</p>
            </button>
        </div>
    </div>

    <nav class="social-links-container">
        <a class="social-links" href="https://www.linkedin.com/in/n-jenkins/" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/In.png" alt="LinkedIn"/> LinkedIn</a>
        <a class="social-links" href="https://github.com/NathanaelJ" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/Git.png" alt="GitHub"/> GitHub</a>
    </nav>
</footer>




<style>
/* NAV MENU */
/* menu link defaults */
.menu-links, .menu-links:visited {
    display: inline-block;
    font-size: var(--font-size-large);
    color: var(--color-text-primary);
    margin: 0 0.5vw;
    padding: var(--spacing-xs) var(--spacing-xs);
    border-bottom: var(--border-width-thin) solid var(--color-border);
}
/* Dropdown settings */
.dropdown{
    position: relative;
    display: inline-block;
}
/* Dropdown Content (Hidden by Default) */
.dropdown-content {
    opacity: 0;
    transition: visibility 1s, opacity 0.25s;
    visibility: hidden;
    position: fixed;
    z-index: 2;
}
/* Links inside the dropdown */
.dropdown-content a {
    display: block;
    color: var(--color-text-primary);
    background: var(--color-hover);
    padding: var(--spacing-xs) var(--spacing-xs);
    min-width: 100%;
    overflow: auto;
    text-decoration: none;
}
/* Dropdown container positioning */
.menu-right {
    display: block;
    float: right;
    text-align: center;
}
/* Change color of dropdown links on hover */
.dropdown-content a:hover {
    background-color: var(--color-text-primary);
    color: var(--color-hover);
    cursor: pointer;
}
/* Show the dropdown menu on hover */
.dropdown:hover .dropdown-content, .dropdown-content:hover{
    opacity: 1;
    transition: visibility 0s, opacity 0.25s;
    visibility: visible;
}
/* Change the background color of the dropdown button */
.dropdown:hover .menu-links {
    background-color: var(--color-hover);
    border-bottom-color: var(--color-accent);
    border-bottom-width: var(--border-width-thick);
}
/* Changes colour of links on hover */
.menu-links:hover {
    background-color: var(--color-hover);
    border-bottom-color: var(--color-accent);
    border-bottom-width: var(--border-width-thickest);
    cursor: pointer;
}
/* Current page indicator */
/* Current page indicator - make more specific and move after hover styles */
.menu-links.current-page {
    border-bottom-color: var(--color-accent-2);
    border-bottom-width: var(--border-width-thickest);
}
.menu-links.current-page:hover {
    border-bottom-width: var(--border-width-thickest);
}

</style>