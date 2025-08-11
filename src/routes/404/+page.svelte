<svelte:head>
  <title>404: Page Not Found</title>
</svelte:head>

<main class="site-main">
  <div class="wrapper">
    <div class="error-container fade-in-up">
      <h1>404: Page Not Found</h1>
      <p>Oops! Looks like you're lost. Here are some dogs to cheer you up:</p>
    </div>

    <div class="projects-grid">
      <article class="project-card">
        <figure>
          <img src="/Dogs/Minnie.jpeg" alt="Minnie the dog" class="project-image" style="height: 400px;" />
          <figcaption>My cousin's dog, Minnie</figcaption>
        </figure>
      </article>

      <article class="project-card">
        <figure>
          <img src="/Dogs/Winnie.jpeg" alt="Winnie the dog (arch-nemesis of Minnie)" class="project-image" style="height: 400px;" />
          <figcaption>My cousin's dog, Winnie (arch-nemesis of Minnie)</figcaption>
        </figure>
      </article>

      <article class="project-card">
        <figure>
          <img src="/Dogs/Emilio.jpeg" alt="My Prof's dog" class="project-image" style="height: 400px;" />
          <figcaption>My prof. brought his dog to class</figcaption>
        </figure>
      </article>

      <article class="project-card">
        <figure>
          <img src="/Dogs/Winchester.jpeg" alt="Busking dog" class="project-image" style="height: 400px;" />
          <figcaption>A dog I saw on the street</figcaption>
        </figure>
      </article>
    </div>

    <div class="text-center" style="margin-top: 2em;">
      <a href="/" class="project-link">Return to Homepage</a>
    </div>
  </div>
</main>


