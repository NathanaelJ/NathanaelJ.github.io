<script>
    export let data = {};
    export let hLevel = 2;
    import { base } from '$app/paths';
</script>

<article class="project-card">
    <img src={data.img} alt="Project Thumbnail" class="project-image"/>
    <div class="project-content">
        <svelte:element this={"h" + hLevel}>{data.title}</svelte:element>
        <h3>{data.subtitle}</h3>
        <p>{data.year}</p>
        <p>{data.description}</p>
        <a href="{base}/{data.link}" class="project-link">View Project</a>
    </div>
</article>

<style>
    /* Project card item */
    .project-card {
        background: var(--color-background);
        border-radius: 8px;
        overflow: hidden;
        transition: transform 0.2s;
        box-shadow: 0 2px 5px var(--color-border);
    }
    .project-card:hover {
        transform: translateY(-5px);
    }
</style>