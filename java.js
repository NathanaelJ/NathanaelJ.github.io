/* Nathanael Jenkins 2021 */
/* Javascript for including header and footer on all pages */

/* SOURCE: https://www.w3schools.com/howto/howto_html_include.asp */
/* Modified by Claude-Sonnet 3.5 */
/* Req. ID 83662fb8-5ce3-4e8f-93b8-a7e8325a4dfa */

function includeHTML(callback) {
  console.log("Including HTML");
  var z, i, elmnt, file, xhttp;
  var remaining = 0; // Counter for remaining requests
  var hasIncludes = false;

  /* Loop through a collection of all HTML elements: */
  z = document.getElementsByTagName("*");
  for (i = 0; i < z.length; i++) {
    elmnt = z[i];
    /*search for elements with a certain attribute:*/
    file = elmnt.getAttribute("w3-include-html");
    if (file) {
      hasIncludes = true;
      remaining++; // Increment counter for each request
      
      /* Make an HTTP request using the attribute value as the file name: */
      (function(elmnt) {  // Create closure to preserve element reference
        xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4) {
            if (this.status == 200) {
              elmnt.innerHTML = this.responseText;
            }
            if (this.status == 404) {
              elmnt.innerHTML = "Page not found.";
            }
            /* Remove the attribute */
            elmnt.removeAttribute("w3-include-html");
            
            remaining--; // Decrement counter when request completes
            // Only execute callback when all requests are done
            if (remaining === 0 && callback) {
              console.log("All HTML includes complete, running callback");
              callback();
            }
          }
        }
        xhttp.open("GET", file, true);
        xhttp.send();
      })(elmnt);
    }
  }
  
  // If no includes were found, execute callback immediately
  if (!hasIncludes && callback) {
    console.log("No HTML includes found, running callback");
    callback();
  }
}