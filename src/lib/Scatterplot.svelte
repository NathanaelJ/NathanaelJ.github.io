<script>
  import * as d3 from "d3";
  import { computePosition, autoPlacement, offset } from '@floating-ui/dom';

  export let commits = [];
  export let selectedCommits = [];
  export let width = 1000;
  export let height = 600;

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

  // Scales
  $: minDate = d3.min(commits.map(d => d.date));
  $: maxDate = d3.max(commits.map(d => d.date));
  $: maxDatePlusOne = new Date(maxDate);
  $: maxDatePlusOne.setDate(maxDatePlusOne.getDate() + 1);
  
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
    if (!event.selection) return;
    
    const [[x0, y0], [x1, y1]] = event.selection;
    
    const brushedCommits = commits.filter(commit => {
      const commitX = xScale(commit.datetime);
      const commitY = yScale(commit.hourFrac);
      return commitX >= x0 && commitX <= x1 && commitY >= y0 && commitY <= y1;
    });

    if (event.type === "end") {
      selectedCommits = [
        ...selectedCommits.filter(commit => !brushedCommits.includes(commit)),
        ...brushedCommits.filter(commit => !selectedCommits.includes(commit))
      ];
      isBrushing = false;
      d3.select(brushGroup).call(brush.move, null);
    } else {
      isBrushing = true;
    }
  }

  $: {
    brush = d3.brush()
      .extent([[usableArea.left, usableArea.top], [usableArea.right, usableArea.bottom]])
      .on("start brush end", brushed);

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
  $: hoveredCommit = commits[hoveredIndex] ?? hoveredCommit ?? {};

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
    else if (evt.type === "click") {
      let commit = commits[index];
      if (isBrushing) {
        if (!selectedCommits.includes(commit)) {
          selectedCommits = [...selectedCommits, commit];
        } else {
          selectedCommits = selectedCommits.filter(c => c !== commit);
        }
      } else {
        if (!selectedCommits.includes(commit)) {
          selectedCommits = [...selectedCommits, commit];
        } else {
          selectedCommits = selectedCommits.filter(c => c !== commit);
        }
      }
    }
  }

  // Scale dots by the number of lines edited
  $: rScale = d3.scaleSqrt(d3.extent(commits, d => d.totalLines), [5, 40]);
  // Scale color by the number of lines edited
  $: colorScale = d3.scaleSqrt(d3.extent(commits, d => d.totalLines), ["#9be9a850", "#216e39B0"]);
</script>

<svg viewBox="0 0 {width} {height}">
  <g transform="translate(0, {usableArea.bottom})" bind:this={xAxis} />
  <g class="gridlines" transform="translate({usableArea.left}, 0)" bind:this={yAxisGridlines} />
  <g transform="translate({usableArea.left}, 0)" bind:this={yAxis} />
  <g class="brush" bind:this={brushGroup} />
  <g class="dots">
    {#each commits.slice(0, -2) as commit, index (commit.id) }
      <circle
        on:mouseenter={evt => dotInteraction(index, evt)}
        on:click={evt => dotInteraction(index, evt)}
        on:mouseleave={evt => dotInteraction(index, evt)}
        class:selected={ selectedCommits.includes(commit) }
        cx={ xScale(commit.datetime) }
        cy={ yScale(commit.hourFrac) }
        r={rScale(commit.totalLines)}
        fill={colorScale(commit.totalLines)}
        class="dot"
        stroke="black"
        stroke-width="1px"
      />
    {/each}
  </g>
</svg>

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
</dl>

<style>
  svg {
    overflow: visible;
  }
  .gridlines {
    stroke-opacity: .2;
  }

  circle {
    transition: 500ms;
    transform-origin: center;
    transform-box: fill-box;

    &:hover {
      transform: scale(1.5);
    }

    /* Doesn't seem to work in Safari, only Chrome */
    @starting-style {
      r: 0;
    }
  }

  .selected {
    fill: rgba(255, 0, 179, 0.6);
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
  }
  
  dl.info[hidden]:not(:hover, :focus-within) {
    opacity: 0;
    visibility: hidden;
  }
  
  dl.info dt {
    text-transform: uppercase;
    text-align: right;
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
  }

  dl.info dd a:hover {
    color: var(--color-accent);
  }

  .tooltip {
    position: fixed;
    top: 1em;
    left: 1em;
  }
</style> 