/* Nathanael Jenkins 2025 */
/* Scripting for controlling dark vs light mode */

/* With assistance from Claude-Sonnet 3.5 */
/* Req. ID d1197fd7-2273-42b9-a5ac-01e7592c4e26 */

// Initialize scheme handling
function initializeScheme() {
  console.log("Initializing light/dark scheme")
  let button = document.querySelector('.color-mode-button');
  console.log("Found button:", button);

  // Get stored Scheme or default to 'auto'
  const storedScheme = localStorage.getItem('color-scheme') || 'auto';
  setScheme(storedScheme);
  updateSchemeIcon(storedScheme, button);

  // Add click event listener to button
  button.addEventListener('click', function() {
    const currentScheme = localStorage.getItem('color-scheme') || 'auto';
    const schemes = ['light', 'dark', 'auto'];
    const nextScheme = schemes[(schemes.indexOf(currentScheme) + 1) % schemes.length];
    setScheme(nextScheme);
    updateSchemeIcon(nextScheme, button);
    console.log("Switched to scheme:", nextScheme);
  });
} 

// Set scheme and update localStorage
function setScheme(mode) {
  if (mode === 'auto') {
    // Remove manual Scheme
    document.documentElement.removeAttribute('color-scheme');
    // Apply Scheme based on system preference
    if (window.matchMedia('(prefers-color-scheme: dark)').matches) {
      document.documentElement.setAttribute('color-scheme', 'dark');
    }
  } else {
    document.documentElement.setAttribute('color-scheme', mode);
  }
  localStorage.setItem('color-scheme', mode);

  // Show/ hide dark mode warnings
  const warning = document.querySelector('.darkModeWarning');
  if (warning) { // (Just an error check)
    warning.style.display = document.documentElement.getAttribute('color-scheme') === 'dark' ? 'block' : 'none';
  }
}

// Update the Scheme text
function updateSchemeIcon(mode, button) {
  const txt = button.querySelector('p') || document.createElement('p');
  while (txt.firstChild) {
    txt.removeChild(txt.firstChild);
  }
  const txtContent = document.createTextNode(`Toggle lighting: ${mode.charAt(0).toUpperCase() + mode.slice(1)}`);
  console.log(`Setting text to: ${txtContent}`);
  txt.appendChild(txtContent);
}

// Listen for system Scheme changes when in auto mode
window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', (e) => {
  if (localStorage.getItem('color-scheme') === 'auto') {
    setScheme('auto');
  }
});