<script>
  import * as d3 from "d3";

  import { onMount } from "svelte";
  import { base } from '$app/paths';
  import Scrolly from "svelte-scrolly";


  import {
    computePosition,
    autoPlacement,
    offset,
  } from '@floating-ui/dom';

  import Bar from '$lib/Bar.svelte';
  import StackedBar from '$lib/StackedBar.svelte';
  import Scatterplot from '$lib/Scatterplot.svelte';
  import FileLines from '$lib/FileLines.svelte';

  let colorScaleBars = d3.scaleOrdinal(d3.schemeTableau10);

  let data = [];
  let commits = [];
  let clickedCommits = [];
  let commitProgress = 100;
  let filteredCommits = [];
  let timeScale;
  let filteredLines = [];


  onMount(async () => {
    data = await d3.csv(`${base}/loc.csv`, row => ({
      ...row,
      line: Number(row.line), // or just +row.line
      depth: Number(row.depth),
      length: Number(row.length),
      date: new Date(row.date + "T00:00" + row.timezone),
      datetime: new Date(row.datetime)
    }));

    commits = d3.groups(data, d => d.commit).map(([commit, lines]) => {
      let first = lines[0];
      let {author, date, time, timezone, datetime} = first;
      let ret = {
        id: commit,
        url: "https://github.com/nathanaelj/6C85/commit/" + commit,
        author, date, time, timezone, datetime,
        hourFrac: datetime.getHours() + datetime.getMinutes() / 60,
        totalLines: lines.length
      };

      // Like ret.lines = lines
      // but non-enumerable so it doesn't show up in JSON.stringify
      Object.defineProperty(ret, "lines", {
        value: lines,
        configurable: true,
        writable: true,
        enumerable: false,
      });

      return ret;
    });
    
    commits = commits.filter(commit => !/^0+$/.test(commit.id)); // Remove commits with id 000000 (corresponding to live commit)

    // Place smaller dots on top
    commits = d3.sort(commits, d => -d.totalLines);

    // console.log(commits);

  }); // END OF onMount


  // Compute commits per period of the day
  $: workByPeriod = d3.rollups(filteredLines, v => v.length, d => d.datetime.toLocaleString("en", {dayPeriod: "short"}))
  $: maxPeriod = d3.greatest(workByPeriod, (d) => d[1])?.[0] || "N/A";



  // Time filtering
  $: minDateTime = d3.min(commits.map(d => d.datetime));
  $: maxDateTime = d3.max(commits.map(d => d.datetime));
  $: maxDateTimePlusOne = new Date(maxDateTime);
  $: maxDateTimePlusOne.setDate(maxDateTimePlusOne.getDate() + 1);
  $: timeScale = d3.scaleTime()
    .domain([minDateTime, maxDateTimePlusOne])
    .range([0, 100])
    .nice();
  $: commitMaxTime = timeScale.invert(commitProgress);
  $: filteredCommits = commits.filter(commit => commit.datetime <= commitMaxTime) 
  $: filteredLines = data.filter(line => line.datetime <= commitMaxTime)


  // Scatter plot of commits by time and day
  let width = 1000, height = 600;
  // Margins
  let margin = {top: 10, right: 10, bottom: 30, left: 20};
  let usableArea = {
    top: margin.top,
    right: width - margin.right,
    bottom: height - margin.bottom,
    left: margin.left
  };

  usableArea.width = usableArea.right - usableArea.left;
  usableArea.height = usableArea.bottom - usableArea.top;
  $: minDate = d3.min(filteredCommits.map(d => d.date));
  $: maxDate = d3.max(filteredCommits.map(d => d.date));
  $: maxDatePlusOne = new Date(maxDate);
  $: maxDatePlusOne.setDate(maxDatePlusOne.getDate() + 1);
  // Scales
  $: xScale = d3.scaleTime()
    .domain([minDate, maxDatePlusOne])
    .range([usableArea.left, usableArea.right])
    .nice();
  $: yScale = d3.scaleLinear()
    .domain([24, 0])
    .range([usableArea.bottom, usableArea.top]);

  // Brush functionality
  let brush;
  let brushGroup;
  let isBrushing = false;

  function brushed(event) {
    if (!event.selection) return; // Ignore "brushed" events when the brush is dropped
    
    const [[x0, y0], [x1, y1]] = event.selection;
    
    // Find commits within the brush selection
    const brushedCommits = filteredCommits.filter(filteredCommits => {
      const commitX = xScale(filteredCommits.datetime);
      const commitY = yScale(filteredCommits.hourFrac);
      return commitX >= x0 && commitX <= x1 && commitY >= y0 && commitY <= y1;
    });

    // Toggle selection state of brushed commits
    if (event.type === "end") {
      clickedCommits = [
        ...clickedCommits.filter(commit => !brushedCommits.includes(commit)), // Keep commits outside brush
        ...brushedCommits.filter(commit => !clickedCommits.includes(commit))  // Add unselected commits from brush
      ];
      isBrushing = false;
      // Clear the brush selection
      d3.select(brushGroup).call(brush.move, null);
    } else {
      isBrushing = true;
    }
  }

  $: {
    // Create brush
    brush = d3.brush()
      .extent([[usableArea.left, usableArea.top], [usableArea.right, usableArea.bottom]])
      .on("start brush end", brushed);

    // Apply brush to the brush group
    d3.select(brushGroup).call(brush);
  }

  let xAxis, yAxis;
  $: {
    d3.select(xAxis).call(d3.axisBottom(xScale));
    d3.select(yAxis).call(d3.axisLeft(yScale));
    d3.select(yAxis).call(d3.axisLeft(yScale).tickFormat(d => String(d % 24).padStart(2, "0") + ":00"));
  }

  // Gridlines
  let yAxisGridlines;
  $: {
    d3.select(yAxisGridlines).call(
      d3.axisLeft(yScale)
        .tickFormat("")
        .tickSize(-usableArea.width)
    );
  }

  // Hover element
  let hoveredIndex = -1;
  $: hoveredCommit = filteredCommits[hoveredIndex] ?? hoveredCommit ?? {};

  let commitTooltip;
  let tooltipPosition = {x: 0, y: 0};

  async function dotInteraction (index, evt) {
    let hoveredDot = evt.target;
    if (evt.type === "mouseenter") {
      hoveredIndex = index;
      tooltipPosition = await computePosition(hoveredDot, commitTooltip, {
        strategy: "fixed",
        middleware: [
          offset(5),
          autoPlacement()
        ],
      });
    }
    else if (evt.type === "mouseleave") {
      hoveredIndex = -1;
    }
    // Clicked dot
    else if (evt.type === "click") {
      let commit = commits[index];
      if (isBrushing) {
        // During brushing, toggle the commit's selection state
        if (!clickedCommits.includes(commit)) {
          clickedCommits = [...clickedCommits, commit];
        } else {
          clickedCommits = clickedCommits.filter(c => c !== commit);
        }
      } else {
        // Normal click behavior
        if (!clickedCommits.includes(commit)) {
          clickedCommits = [...clickedCommits, commit];
        } else {
          clickedCommits = clickedCommits.filter(c => c !== commit);
        }
      }
    }
  }

  // Scale dots by the number of lines edited
  $: rScale = d3.scaleSqrt(d3.extent(commits, d => d.totalLines), [5, 40]);
  // Scale color by the number of lines edited
  $: colorScale = d3.scaleSqrt(d3.extent(commits, d => d.totalLines), ["#9be9a850", "#216e39B0"]);


  // Bar chart
  $: allTypes = Array.from(new Set(data.map(d => d.type)));
  $: selectedLines = (clickedCommits.length > 0 ? clickedCommits : filteredCommits).flatMap(d => d.lines);
  $: selectedCounts = d3.rollup(
      selectedLines,
      v => v.length,
      d => d.type
  );
  $: languageBreakdown = allTypes.map(type => [type, selectedCounts.get(type) || 0]);


</script>

<svelte:head>
  <title>Meta | N Jenkins</title>
</svelte:head>

<main class="site-main">
    <div class="wrapper">
        <h1>Meta</h1>
        <p>This page includes stats about the code in this website.<br/><br/></p>
        <!-- <p>Total lines of code: {data.length}</p> -->

        <section class="processing-box">
          <dl class="stats">
            <dt>Total <abbr title="Lines of code">LOC</abbr></dt>
            <dt>Most common time of day</dt>
            <dd>{filteredLines.length}</dd>
            <dd>{maxPeriod}</dd>
          </dl>
      </section>

      <br/><br/>

      <div class="heading-container">
        <h3>Commits by time of day</h3>
        <button 
          class="clear-button" 
          on:click={() => clickedCommits = []}
          disabled={clickedCommits.length === 0}
        >
          Clear Selection
        </button>
      </div>

      <div class="slider-container">
        <input style="flex: 1;"type="range" min={minDateTime} max={maxDateTimePlusOne} bind:value={commitProgress} />
        <time datetime={commitMaxTime instanceof Date && !isNaN(commitMaxTime) ? commitMaxTime.toISOString() : ''}>{commitMaxTime instanceof Date && !isNaN(commitMaxTime) ? commitMaxTime.toLocaleString("en", {dateStyle: "medium", timeStyle: "short"}) : 'Invalid date'}</time>
      </div>

      <Scrolly bind:progress={ commitProgress }>
        <!-- Story here -->
        {#each commits as commit, index }
          <p>
            On {commit.datetime.toLocaleString("en", {dateStyle: "full", timeStyle: "short"})},
            {index === 0 
              ? "I set forth on my very first commit, beginning a magical journey of code. You can view it "
              : "I added another enchanted commit, each line sparkling with a touch of wonder. See it "}
            <a href="{commit.url}" target="_blank">
              {index === 0 ? "here" : "here"}
            </a>.
            This update transformed {commit.totalLines} lines across { d3.rollups(commit.lines, D => D.length, d => d.file).length } files.
            With every commit, our project grows into a kingdom of dreams.
          </p>
        {/each}
        <svelte:fragment slot="viz">
          <!-- Visualizations here -->
            <Scatterplot 
            commits={filteredCommits} 
            bind:selectedCommits={clickedCommits}
          />
    
          <StackedBar data={languageBreakdown} width={500} colorScale={colorScaleBars}/>
          
          <dl class="info tooltip" hidden={hoveredIndex === -1} style="top: {tooltipPosition.y}px; left: {tooltipPosition.x}px" bind:this={commitTooltip}>
            <dt>Commit</dt>
            <dd><a href="{ hoveredCommit.url }" target="_blank">{ hoveredCommit.id }</a></dd>
            <dt>Date</dt>
            <dd>{ hoveredCommit.datetime?.toLocaleString("en", {dateStyle: "full"}) }</dd>
            <dt>Time</dt>
            <dd>{ hoveredCommit.datetime?.toLocaleString("en", {timeStyle: "short"}) }</dd>
            <dt>Author</dt>
            <dd>{ hoveredCommit.author }</dd>
            <dt>Lines edited</dt>
            <dd>{ hoveredCommit.totalLines }</dd>
          
            <!-- Add: Time, author, lines edited -->
          </dl>
        </svelte:fragment>
      </Scrolly>

      <Scrolly bind:progress={commitProgress} --scrolly-layout="viz-first">
        {#each commits as commit, index }
          <p>
            On {commit.datetime.toLocaleString("en", {dateStyle: "full", timeStyle: "short"})},
            {index === 0 
              ? "I set forth on my very first commit, beginning a magical journey of code. You can view it "
              : "I added another enchanted commit, each line sparkling with a touch of wonder. See it "}
            <a href="{commit.url}" target="_blank">
              {index === 0 ? "here" : "here"}
            </a>.
            This update transformed {commit.totalLines} lines across { d3.rollups(commit.lines, D => D.length, d => d.file).length } files.
            With every commit, our project grows into a kingdom of dreams.
          </p>
        {/each}
        <svelte:fragment slot="viz">
          <!-- Visualizations here -->
          <FileLines lines={filteredLines} width={width} colorScale={colorScaleBars}/>
        </svelte:fragment>
        
      </Scrolly>
      

      
    </div>
</main>

<style>

  dl {
      grid-template-columns: repeat(2, 1fr);
  }

  dl.info {
    background-color: var(--color-background);
    box-shadow: 0 2px 5px var(--color-border);
    border-radius: 8px;
    padding: var(--spacing-md);

    transition-duration: 500ms;
    transition-property: opacity, visibility;

    display: grid;
    grid-template-columns: auto 1fr;
    margin: 0;

    opacity: 0.9;

    &[hidden]:not(:hover, :focus-within) {
      opacity: 0;
      visibility: hidden;
    }
  }
  
  dl.info dt {
      text-transform: uppercase;
      text-align: right;
      /* padding-right: var(--spacing-sm); */
      color: var(--color-text-secondary);
      font-size: var(--font-size-small);
      margin: 0;
      padding: 0;
  }
  
  dl.info dd {
      font-family: var(--font-primary);
      font-weight: bold;
      font-size: var(--font-size-small);
      text-align: left;
      margin: 0;
      padding: 0;
  }
  dl.info dd a {
    text-decoration: underline;
    color: var(--color-text-primary);
    font-size: var(--font-size-small);
    /* font-weight: bold; */
  }

  dl.info dd a:hover {
    color: var(--color-accent);
  }
  .tooltip {
      position: fixed;
      top: 1em;
      left: 1em;
  }

  .heading-container {
    display: flex;
    align-items: center;
    justify-content: space-between;
    margin-bottom: 1rem;
  }

  .heading-container h3 {
    margin: 0;
  }

  .clear-button {
    padding: 0.25rem 0.75rem;
    background: var(--color-accent);
    color: white;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: var(--font-size-small);
    transition: background-color 0.2s;
  }

  .clear-button:hover:not(:disabled) {
    background: var(--color-accent-2);
  }

  .clear-button:disabled {
    background: var(--color-border);
    cursor: not-allowed;
    opacity: 0.7;
  }

  .slider-container {
    display: flex;
    flex-direction: column;
    align-items: right;
    justify-content: space-between;
    margin-bottom: 1rem;
  }

  .slider-container input {
    width: 100%;
  }
  

</style>