<script>
    import { onMount } from 'svelte';
    import { browser } from '$app/environment';
    import { page } from '$app/stores';

    let location = null;
    let error = null;
    let loading = true;
    let aircraft = null;

    // Function to calculate distance between two points using Haversine formula
    function calculateDistance(lat1, lon1, lat2, lon2) {
        const R = 6371; // Earth's radius in km
        const dLat = (lat2 - lat1) * Math.PI / 180;
        const dLon = (lon2 - lon1) * Math.PI / 180;
        const a = 
            Math.sin(dLat/2) * Math.sin(dLat/2) +
            Math.cos(lat1 * Math.PI / 180) * Math.cos(lat2 * Math.PI / 180) * 
            Math.sin(dLon/2) * Math.sin(dLon/2);
        const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
        return R * c;
    }

    async function getLocation() {
        if (!browser) return;
        
        try {
            const position = await new Promise((resolve, reject) => {
                navigator.geolocation.getCurrentPosition(resolve, reject, {
                    enableHighAccuracy: true,
                    timeout: 5000,
                    maximumAge: 0
                });
            });

            location = {
                lat: position.coords.latitude,
                lon: position.coords.longitude
            };

            // Fetch aircraft data from adsb.fi through CORS proxy
            const baseUrl = `https://opendata.adsb.fi/api/v2/lat/${location.lat}/lon/${location.lon}/dist/100`;
            const proxyUrl = `https://api.allorigins.win/get?url=${encodeURIComponent(baseUrl)}`;
            
            const response = await fetch(proxyUrl);
            if (!response.ok) throw new Error('Failed to fetch aircraft data');
            
            const proxyData = await response.json();
            const data = JSON.parse(proxyData.contents);
            
            if (data.aircraft && data.aircraft.length > 0) {
                // Sort by distance and get closest
                const closestAircraft = data.aircraft.sort((a, b) => a.dst - b.dst)[0];
                aircraft = {
                    ...closestAircraft,
                    calculatedDistance: closestAircraft.dst
                };
            } else {
                aircraft = null;
            }
        } catch (e) {
            console.error('Error:', e);
            error = e.message;
            // Fall back to default data if available
            if ($page.data.defaultAircraft?.aircraft?.length > 0) {
                aircraft = $page.data.defaultAircraft.aircraft[0];
            }
        } finally {
            loading = false;
        }
    }

    onMount(() => {
        // Start with default data if available
        if ($page.data.defaultAircraft?.aircraft?.length > 0) {
            aircraft = $page.data.defaultAircraft.aircraft[0];
            loading = false;
        }
        // Then try to get real location data
        getLocation();
    });
</script>

<section class="processing-box">
    <h2 style="font-style: normal; font-family: var(--font-primary); font-size: var(--font-size-xlarge); text-align: center;">
        {loading ? 'Finding' : 'Your'} Closest Aircraft
    </h2>

    {#if loading && !aircraft}
        <p>Getting your location and finding nearby aircraft...</p>
    {:else if error && !aircraft}
        <p class="error">Error: {error}</p>
    {:else if aircraft}
        <dl>
            <dt>Flight Number</dt>
            <dt>Aircraft Type</dt>
            <dt>Altitude</dt>
            <dt>Distance</dt>
            <dd>{aircraft.flight?.trim() || 'Unknown'}</dd>
            <dd>{aircraft.desc || aircraft.t || 'Unknown'}</dd>
            <dd>{aircraft.alt_baro === 'ground' ? 'On Ground' : `${Math.round(aircraft.alt_baro)} ft`}</dd>
            <dd>{Math.round(aircraft.dst)} km</dd>
        </dl>
        {#if loading}
            <p class="note">Updating with your location...</p>
        {/if}
    {:else}
        <p>No aircraft found within 100km</p>
    {/if}
</section>

<style>
    dl {
        display: grid;
        grid-template-columns: repeat(4, 1fr);
        gap: var(--spacing-md);
        margin-top: var(--spacing-md);
    }

    dt {
        font-family: var(--font-primary);
        font-size: var(--font-size-normal);
        color: var(--color-text-secondary);
        text-align: center;
    }

    dd {
        font-family: var(--font-primary);
        font-size: var(--font-size-large);
        color: var(--color-text-primary);
        text-align: center;
        margin: 0;
        padding: var(--spacing-xs) 0;
    }

    .error {
        color: var(--color-error);
        text-align: center;
    }

    .note {
        font-size: var(--font-size-small);
        color: var(--color-text-secondary);
        text-align: center;
        margin-top: var(--spacing-xs);
        font-style: italic;
    }
</style> 