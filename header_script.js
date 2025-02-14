// Function to highlight current page in navigation
function highlightCurrentPage() {
    console.log("Header script starting...");
    
    // Get current page filename
    const currentPage = window.location.pathname.split("/").pop();
    console.log("Current page:", currentPage);
    
    // Map filenames to their corresponding link IDs
    const pageMap = {
        "index.html": "home-link",
        "contact_labs.html": "contact-link",
        "projects_labs.html": "projects-link",
        "resume_labs.html": "resume-link",
        "A2.html": "a2-link"
    };
    
    console.log("Checking if", currentPage, "is in pageMap");
    
    // Add current-page class to the active link
    if (currentPage in pageMap || currentPage === "") {
        console.log("Found matching page in pageMap or blank page");
        // If blank page or index.html, highlight home
        const pageId = (currentPage === "" || currentPage === "index.html") ? "home-link" : pageMap[currentPage];
        const element = document.getElementById(pageId);
        console.log("Looking for element with ID:", pageId);
        
        if (element) {
            console.log("Found element, adding current-page class");
            element.classList.add("current-page");
            
            // Also highlight Projects when on A2.html
            if (currentPage === "A2.html") {
                console.log("On A2.html, also highlighting projects link");
                const projectsLink = document.getElementById("projects-link");
                if (projectsLink) {
                    projectsLink.classList.add("current-page");
                }
            }
        } else {
            console.log("Element not found!");
        }
    } else {
        console.log("Page not found in pageMap");
    }
} 