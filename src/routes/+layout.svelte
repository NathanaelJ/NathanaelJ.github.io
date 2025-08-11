<script>
    import { base } from '$app/paths';
    import { page } from "$app/stores";

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
                <a class="menu-links" href="{base}/Projects" class:current-page={routeId.includes("/Projects")} id="projects-link">Projects</a>
                <div class="dropdown-content">
                    <a href="{base}/dataviz" id="dataviz-link">Data Visualization</a>
                    <a href="{base}/Projects/Thesis" id="FYP-link">Thesis</a>
                    <a href="{base}/Projects/Modelling" id="modeling-link">CAD Models</a>
                    <a href="{base}/Projects/ICLR" id="ICLR-link">Rocketry</a>
                    <a href="{base}/Projects/Academic" id="OtherProj-link">Other</a>
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

    <div class="footer-nav-row">
        <nav class="contacts">
            <a class="menu-links" style="border-bottom: none;" href="mailto:naj20@mit.edu">naj20@mit.edu</a>
            <!--<a class="menu-links" href="tel:07960264171">+44(0) 7960 264171</a>-->
        </nav>
    </div>

    <nav class="social-links-container">
        <a class="social-links" href="https://www.linkedin.com/in/n-jenkins/" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/In.png" alt="LinkedIn"/> LinkedIn</a>
        <a class="social-links" href="https://github.com/NathanaelJ" target="_blank" rel="noreferrer noopener"><img class="logo" src="/resources-General/Git.png" alt="GitHub"/> GitHub</a>
    </nav>
</footer>