<script>
    export let data = {};
    export let hLevel = 2;
    import { base } from '$app/paths';
    
    $: projectLink = data.link.startsWith('external:') 
        ? data.link.replace('external:', '') 
        : `${base}/${data.link}`;
    
    $: isExternal = data.link.startsWith('external:');
</script>

<article class="project-card">
    <img src={data.img} alt="Project Thumbnail" class="project-image"/>
    <div class="project-content">
        <svelte:element this={"h" + hLevel}>{data.title}</svelte:element>
        <h3>{data.subtitle}</h3>
        <p>{data.year}</p>
        <p>{data.description}</p>
        <a href={projectLink} 
           class="project-link" 
           target={isExternal ? "_blank" : undefined}
           rel={isExternal ? "noopener noreferrer" : undefined}>
            View Project {#if isExternal}<span class="external-link-icon">⇱</span>{/if}
        </a>
    </div>
</article>