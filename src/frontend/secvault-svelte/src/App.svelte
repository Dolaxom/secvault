<script lang="ts">
  import { onMount } from "svelte";
  import { writable } from "svelte/store";

  let secretInput = "";
  let passwordInput = "";
  let firstTokenGenerated = "";
  let secondTokenGenerated = "";
  let firstTokenInput = "";
  let secondTokenInput = "";
  let retrievedSecret = "";
  let githubStars = writable(0);

  async function writeSecret() {
    const response = await fetch("http://localhost:8090/api/v1/secret/write", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ secret: secretInput, password: passwordInput }),
    });
    const data = await response.json();

    firstTokenGenerated = data.first;
    secondTokenGenerated = data.second;
  }

  async function readSecret() {
    const response = await fetch(
      `http://localhost:8090/api/v1/secret/read?token1=${firstTokenInput}&token2=${secondTokenInput}`,
    );
    const data = await response.json();
    retrievedSecret = data.secret;
  }

  async function fetchGitHubStars() {
    const response = await fetch(
      "https://api.github.com/repos/Dolaxom/secvault",
    );
    const data = await response.json();
    githubStars.set(data.stargazers_count || 0);
  }

  onMount(fetchGitHubStars);
</script>

<header>
  <div class="header-wrapper">
    <img src="/sv.svg" width="50" height="50" alt="Icon" />
    <a href="https://github.com/Dolaxom/secvault" target="_blank">
      <img
        src="https://img.shields.io/github/stars/Dolaxom/secvault?style=social"
        alt="GitHub stars"
      />
    </a>
  </div>
</header>
<div class="container">
  <div class="box">
    <h1 id="title">SecVault</h1>
    <p id="description">
      <strong>Securely</strong> share your most sensitive data with confidence
      using our
      <strong>open-source</strong>, end-to-end encrypted platform.
    </p>
    <p><a id="whyus" href="@">Why trust us?</a></p>
    <section class="section">
      <h2 id="bigger">Store a Secret</h2>

      <form on:submit|preventDefault={writeSecret}>
        <input
          type="text"
          bind:value={secretInput}
          placeholder="Enter your secret"
          required
        />
        <br />
        <input
          type="text"
          bind:value={passwordInput}
          placeholder="Enter a password"
          required
        />
        <br />
        <button type="submit" id="btn">Save Secret</button>
      </form>
      <div>
        <p id="output">First Token: {firstTokenGenerated}</p>
        <p id="output">Second Token: {secondTokenGenerated}</p>
      </div>
    </section>
    <section class="section">
      <h2 id="bigger">Retrieve a Secret</h2>
      <input
        type="text"
        bind:value={firstTokenInput}
        placeholder="Enter first token"
      />
      <br />
      <input
        type="text"
        bind:value={secondTokenInput}
        placeholder="Enter second token"
      />
      <br />
      <button id="btn" on:click={readSecret}>Retrieve Secret</button>
      <div>
        <p id="output" class="secret">Secret: {retrievedSecret}</p>
      </div>
    </section>
  </div>
</div>
