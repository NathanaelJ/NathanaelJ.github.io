<svelte:head>
  <title>Contact Form | N Jenkins</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
      <h1>Contact</h1>
      <p><br/></p>
      
      <form action="mailto:naj20@mit.edu" method="GET">
          <div class="form-group">
              <label for="email">Your Email:</label>
              <input type="email" id="email" name="email" required class="form-input">
          </div>
          
          <div class="form-group">
              <label for="subject">Subject:</label>
              <input type="text" id="subject" name="subject" required class="form-input">
          </div>
          
          <div class="form-group">
              <label for="body">Message:</label>
              <textarea id="body" name="body" required class="form-input"></textarea>
          </div>
          
          <div class="submit-button-container">
              <button class="submit-button">Send Email</button>
          </div>
      </form>
  </div>
</main>