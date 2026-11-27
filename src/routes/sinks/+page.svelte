<script>
    // Hidden page: not linked from the menu and not listed in sitemap.xml.
    // Reviews live in src/lib/sinks.json; photos go in static/sinks/.
    //
    // Entry format (all fields optional except name; scores are 0–5, halves allowed):
    // {
    //   "name": "Stata Center, 3rd floor",
    //   "location": "MIT Building 32, Cambridge MA",
    //   "date": "2026-11-27",
    //   "reviewer": "Nat",
    //   "photo": "stata-3.jpg",            // file in static/sinks/ (or a full URL)
    //   "summary": "One-line verdict.",
    //   "ratings": {
    //     "aesthetics":   { "score": 4,   "notes": "..." },
    //     "splash":       { "score": 2.5, "notes": "..." },
    //     "practicality": { "score": 3,   "notes": "..." },
    //     "ratio":        { "score": 5,   "notes": "..." },
    //     "total":        { "score": 4,   "notes": "..." }
    //   }
    // }
    import { base } from '$app/paths';
    import sinks from '$lib/sinks.json';

    const categories = [
        { key: 'aesthetics', label: 'Aesthetics' },
        { key: 'splash', label: 'Splash factor' },
        { key: 'practicality', label: 'Practicality' },
        { key: 'ratio', label: 'Sink-to-counter ratio' },
        { key: 'total', label: 'Total' }
    ];

    let sortBy = 'date';

    const score = (sink, key) => {
        const s = Number(sink?.ratings?.[key]?.score);
        return Number.isFinite(s) ? Math.max(0, Math.min(5, s)) : null;
    };

    const photoSrc = (photo) => (/^(https?:)?\/\//.test(photo) || photo.startsWith('/') ? photo : `${base}/sinks/${photo}`);

    const formatDate = (d) => {
        const date = new Date(`${d}T12:00:00`);
        return isNaN(date) ? d : date.toLocaleDateString('en-GB', { day: 'numeric', month: 'short', year: 'numeric' });
    };

    $: sorted = [...sinks].sort((a, b) =>
        sortBy === 'total'
            ? (score(b, 'total') ?? -1) - (score(a, 'total') ?? -1)
            : sortBy === 'name'
              ? (a.name || '').localeCompare(b.name || '')
              : (b.date || '').localeCompare(a.date || '')
    );
</script>

<svelte:head>
    <title>Sinks | N Jenkins</title>
    <meta name="robots" content="noindex, nofollow" />
</svelte:head>

<main class="site-main">
    <div class="wrapper">
        <div class="page-header">
            <h1>Rate. That. Sink.</h1>
            <p>A highly scientific review of sinks.</p>
        </div>

        {#if sinks.length === 0}
            <p class="empty">No sinks reviewed yet.</p>
        {:else}
            <div class="toolbar">
                <span>{sinks.length} {sinks.length === 1 ? 'sink' : 'sinks'} reviewed</span>
                <label>
                    Sort by
                    <select bind:value={sortBy}>
                        <option value="date">Most recent</option>
                        <option value="total">Highest total</option>
                        <option value="name">Name</option>
                    </select>
                </label>
            </div>

            <div class="sink-list">
                {#each sorted as sink}
                    <article class="sink">
                        <div class="sink-photo">
                            {#if sink.photo}
                                <a href={photoSrc(sink.photo)} target="_blank" rel="noreferrer noopener">
                                    <img src={photoSrc(sink.photo)} alt="Photo of {sink.name}" loading="lazy" />
                                </a>
                            {:else}
                                <div class="no-photo">No photo</div>
                            {/if}
                        </div>

                        <div class="sink-body">
                            <header class="sink-header">
                                <h2>{sink.name}</h2>
                                {#if sink.location || sink.date || sink.reviewer}
                                    <p class="meta">
                                        {[sink.location, sink.date && formatDate(sink.date), sink.reviewer && `Reviewed by ${sink.reviewer}`]
                                            .filter(Boolean)
                                            .join('\u2002·\u2002')}
                                    </p>
                                {/if}
                                {#if sink.summary}<p class="summary">{sink.summary}</p>{/if}
                            </header>

                            <dl class="ratings">
                                {#each categories as cat}
                                    {@const s = score(sink, cat.key)}
                                    <div class="rating" class:total={cat.key === 'total'}>
                                        <dt>{cat.label}</dt>
                                        <dd class="score">
                                            {#if s === null}
                                                <span class="unrated">Not rated</span>
                                            {:else}
                                                <span class="stars" role="img" aria-label="{s} out of 5 stars">
                                                    <span class="stars-empty" aria-hidden="true">★★★★★</span>
                                                    <span class="stars-full" aria-hidden="true" style="width: {(s / 5) * 100}%">★★★★★</span>
                                                </span>
                                                <span class="num">{s}/5</span>
                                            {/if}
                                        </dd>
                                        {#if sink.ratings?.[cat.key]?.notes}
                                            <dd class="notes">{sink.ratings[cat.key].notes}</dd>
                                        {/if}
                                    </div>
                                {/each}
                            </dl>
                        </div>
                    </article>
                {/each}
            </div>
        {/if}
    </div>
</main>

<style>
    .empty {
        color: var(--color-text-light);
        font-style: italic;
    }

    .toolbar {
        display: flex;
        justify-content: space-between;
        align-items: center;
        gap: var(--spacing-4);
        margin-bottom: var(--spacing-6);
        font-family: var(--font-primary);
        font-size: var(--font-size-sm);
        color: var(--color-text-light);
    }

    .toolbar select {
        margin-left: var(--spacing-2);
        font: inherit;
        color: var(--color-text-primary);
        background: var(--color-surface);
        border: 1px solid var(--color-border);
        padding: var(--spacing-1) var(--spacing-2);
    }

    .sink-list {
        display: flex;
        flex-direction: column;
        gap: var(--spacing-8);
    }

    .sink {
        display: grid;
        grid-template-columns: minmax(0, 2fr) minmax(0, 3fr);
        gap: var(--spacing-6);
        padding-bottom: var(--spacing-8);
        border-bottom: 1px solid var(--color-border);
    }

    .sink:last-child {
        border-bottom: none;
    }

    .sink-photo img,
    .no-photo {
        display: block;
        width: 100%;
        aspect-ratio: 4 / 3;
        object-fit: contain;
        border: 1px solid var(--color-border);
        background: var(--color-surface);
    }

    .no-photo {
        display: flex;
        align-items: center;
        justify-content: center;
        color: var(--color-text-light);
        font-family: var(--font-primary);
        font-size: var(--font-size-sm);
    }

    .sink-header h2 {
        margin: 0;
    }

    .meta {
        margin: var(--spacing-1) 0 0;
        font-family: var(--font-primary);
        font-size: var(--font-size-sm);
        color: var(--color-text-light);
    }

    .summary {
        margin: var(--spacing-3) 0 0;
        font-style: italic;
    }

    .ratings {
        margin: var(--spacing-4) 0 0;
    }

    .rating {
        display: grid;
        grid-template-columns: 11rem 1fr;
        column-gap: var(--spacing-4);
        align-items: baseline;
        padding: var(--spacing-2) 0;
        border-top: 1px solid var(--color-border);
    }

    .rating dt {
        font-family: var(--font-primary);
        font-size: var(--font-size-sm);
        color: var(--color-text-secondary);
    }

    .rating dd {
        margin: 0;
    }

    .rating .notes {
        grid-column: 2;
        margin-top: var(--spacing-1);
        font-size: var(--font-size-sm);
        color: var(--color-text-secondary);
        line-height: 1.5;
    }

    .rating.total {
        border-top: 2px solid var(--color-text-primary);
        margin-top: var(--spacing-2);
        padding-top: var(--spacing-3);
    }

    .rating.total dt {
        font-weight: 700;
        color: var(--color-text-primary);
    }

    .rating.total .stars {
        font-size: var(--font-size-xl);
    }

    .score {
        display: flex;
        align-items: center;
        gap: var(--spacing-2);
    }

    .stars {
        position: relative;
        display: inline-block;
        font-size: var(--font-size-lg);
        line-height: 1;
        letter-spacing: 0.1em;
        white-space: nowrap;
    }

    .stars-empty {
        color: var(--color-border);
    }

    .stars-full {
        position: absolute;
        top: 0;
        left: 0;
        overflow: hidden;
        color: var(--color-bronze);
    }

    .num {
        font-family: var(--font-primary);
        font-size: var(--font-size-xs);
        color: var(--color-text-light);
    }

    .unrated {
        font-family: var(--font-primary);
        font-size: var(--font-size-sm);
        font-style: italic;
        color: var(--color-text-light);
    }

    @media (max-width: 720px) {
        .sink {
            grid-template-columns: 1fr;
            gap: var(--spacing-4);
        }

        .rating {
            grid-template-columns: 1fr;
            row-gap: var(--spacing-1);
        }

        .rating .notes {
            grid-column: 1;
        }
    }
</style>
