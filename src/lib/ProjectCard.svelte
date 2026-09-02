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
    <a href={projectLink} 
            target={isExternal ? "_blank" : undefined}
            rel={isExternal ? "noopener noreferrer" : undefined}>
        <img src={data.img} alt="Project Thumbnail" class="project-image"/>
        <div class="project-content">
            <div class="position-line">
                <svelte:element this={"h" + hLevel}>{data.title}</svelte:element>
                <span class="date-range">{data.year}</span>
            </div>
            <h3>{data.subtitle}</h3>
            <!-- <p>{data.description}</p> -->
        </div>
    </a>
</article>