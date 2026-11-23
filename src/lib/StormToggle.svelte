<script>
    import { storm, strike } from '$lib/lightning/index.js';
    import { unlockAudio } from '$lib/lightning/thunder.js';

    let button;

    function toggle() {
        const on = !$storm;
        if (on) unlockAudio();
        storm.set(on);
        if (on) strike(button, { sound: true });
    }
</script>

<button
    bind:this={button}
    class="storm-toggle"
    class:on={$storm}
    type="button"
    aria-pressed={$storm}
    aria-label="Storm mode"
    title={$storm ? 'Calm the storm' : 'Summon a storm'}
    on:click={toggle}
>
    <svg viewBox="0 0 24 24" aria-hidden="true">
        <path d="M13.5 2 4.5 13.5h6.2L9 22l9.5-12.2h-6.3L13.5 2Z" />
    </svg>
</button>
