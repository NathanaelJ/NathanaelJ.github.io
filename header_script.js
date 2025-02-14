// Function to highlight current page in navigation
function highlightCurrentPage() {
    console.log("Header script starting...");
    
    // Get current page pathname
    const currentPath = window.location.pathname;
    console.log("Current path:", currentPath);
    
    // Check if we're in a portfolio directory
    const isPortfolio = currentPath.includes('portfolio');
    console.log("Is portfolio page:", isPortfolio);
    
    // Show/hide subtitle based on directory
    const subtitle = document.querySelector('.title-block .subtitle');
    if (subtitle) {
        subtitle.style.display = isPortfolio ? 'block' : 'none';
    }
    
    // Get current page filename and path segments
    const pathSegments = currentPath.split("/");
    const currentPage = pathSegments.pop();
    console.log("Current page:", currentPage);
    
    // Map filenames to their corresponding link IDs
    const pageMap = {
        "index.html": "home-link",
        "projects.html": "projects-link",
        "resume.html": "resume-link",
    };
    
    // Check if we're in a Projects subdirectory or on a project-related page
    const isProjectPage = pathSegments.includes('Projects') || 
        ["FYP.html", "Modelling.html", "ICLR.html", "Academic.html", "dataviz.html"].includes(currentPage);
    
    if (isProjectPage) {
        // Highlight the main Projects link
        const projectsLink = document.getElementById("projects-link");
        if (projectsLink) {
            projectsLink.classList.add("current-page");
        }
    } else if (currentPage in pageMap || currentPage === "") {
        // Handle non-project pages
        const pageId = (currentPage === "" || currentPage === "index.html") ? "home-link" : pageMap[currentPage];
        const element = document.getElementById(pageId);
        
        if (element) {
            element.classList.add("current-page");
        }
    }
} 