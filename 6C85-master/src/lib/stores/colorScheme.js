import { writable, get } from 'svelte/store';
import { browser } from '$app/environment';

// Initialize with stored value or 'auto'
const storedScheme = browser ? localStorage.getItem('color-scheme') || 'auto' : 'auto';
export const colorScheme = writable(storedScheme);

// Function to set scheme and update localStorage
export function setScheme(mode) {
    if (browser) {
        if (mode === 'auto') {
            document.documentElement.removeAttribute('color-scheme');
            if (window.matchMedia('(prefers-color-scheme: dark)').matches) {
                document.documentElement.setAttribute('color-scheme', 'dark');
            }
        } else {
            document.documentElement.setAttribute('color-scheme', mode);
        }
        localStorage.setItem('color-scheme', mode);
        colorScheme.set(mode);
    }
}

// Function to cycle through schemes
export function cycleScheme() {
    const schemes = ['light', 'dark', 'auto'];
    const currentScheme = get(colorScheme);
    const nextScheme = schemes[(schemes.indexOf(currentScheme) + 1) % schemes.length];
    setScheme(nextScheme);
}

// Initialize the color scheme immediately if we're in the browser
if (browser) {
    setScheme(storedScheme);
} 