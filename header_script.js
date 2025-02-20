/* Nathanael Jenkins 2025 */
/* Scripting for controlling header naviation page selection */

// Function to highlight current page in navigation
function highlightCurrentPage() {
    console.log("Highlighting current page")
    
    // Get current pathname
    const currentPath = window.location.pathname;
    console.log("Current path:", currentPath);
    
    // ========== 6.C85 Portfolio ==========
    // Check if inside 6.C85 portfolio
    const isPortfolio = currentPath.includes('portfolio');
    console.log("Portfolio page?", isPortfolio);
    
    // Show/hide subtitle and portfolio menu item based on directory
    const subtitle = document.querySelector('.title-block .subtitle');
    const portfolioLink = document.querySelector('.portfolio-only');
    if (subtitle) { // (Just an error check)
        subtitle.style.display = isPortfolio ? 'block' : 'none';
    }
    if (portfolioLink) { // (Just an error check)
        portfolioLink.style.display = isPortfolio ? 'inline-block' : 'none';
        // Highlight portfolio link as current page if inside portfolio
        if (isPortfolio) {
            portfolioLink.classList.add("current-page");
        }
    }

    // ========== All Pages ==========
    // Clean up pathname (separate page filename from rest of path)
    const pathSegments = currentPath.split("/");
    const currentPage = pathSegments.pop();
    console.log("Current page:", currentPage);
    
    // Page name map (excluding projects)
    const pageMap = {
        "index.html": "home-link",
        "Projects.html": "projects-link",
        "resume.html": "resume-link",
        "dataviz.html": "portfolio-link"
    };
    
    // Check if we're in a Projects subdirectory or on a project-related page
    const isProjectPage = pathSegments.includes('Projects') || 
        ["FYP.html", "Modelling.html", "ICLR.html", "Academic.html", "dataviz.html"].includes(currentPage);
    
    if (isProjectPage) {
        // Highlight the main Projects link
        const projectsLink = document.getElementById("projects-link");
        if (projectsLink) { // (Just an error check)
            projectsLink.classList.add("current-page");
        }
    } else if (currentPage in pageMap || currentPage === "") {
        // Handle non-project pages (with scope for index calls when page name is empty)
        const pageId = (currentPage === "" || currentPage === "index.html") ? "home-link" : pageMap[currentPage];
        const element = document.getElementById(pageId);
        
        if (element) { // (Just an error check)
            element.classList.add("current-page");
        }
    }
} 