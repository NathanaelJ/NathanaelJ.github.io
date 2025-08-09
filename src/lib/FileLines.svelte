<script>
  import * as d3 from "d3";

  export let lines = [];
  export let width = 400;
  export let colorScale = d3.scaleOrdinal(d3.schemeTableau10);

  let files = [];
  let svg;
  $: files = d3.groups(lines, d => d.file)
              .map(([name, lines]) => ({ name, lines }));
  $: files = files.sort((a, b) => b.lines.length - a.lines.length);

  let previousDotCounts = new Map();


  const firstColumnWidth = 150;
  const fileInfoMargin = 100;
  const dotsColumnX = firstColumnWidth + fileInfoMargin;
  const approxDotWidth = 15;
  const linesPerDot = 5;
  const baseY = 30;
  const totalLinesOffset = 15;
  const fileInfoHeight = baseY + totalLinesOffset;
  const dotRowHeight = 7;

  function generateDots(file, svgWidth) {
    const totalDots = Math.ceil(file.lines.length / linesPerDot);
    const availableWidth = svgWidth - dotsColumnX;
    const maxDotsPerRow = Math.floor(availableWidth / approxDotWidth) || totalDots;
    let tspans = "";
    const dotRows = Math.ceil(totalDots / maxDotsPerRow);
    for (let r = 0; r < dotRows; r++) {
      const rowLines = file.lines.slice(r * maxDotsPerRow, (r + 1) * maxDotsPerRow);
      const rowDots = rowLines
        .map((line, i) => `<tspan class="dot" data-index="${r * maxDotsPerRow + i}" style="fill:${colorScale(line.type)}">•</tspan>`)
        .join('');

      tspans += `<tspan x="${dotsColumnX}" dy="${r === 0 ? 0 : dotRowHeight + 'px'}">${rowDots}</tspan>`;
    }
    return tspans;
  }

  $: filesWithHeights = files.map(file => {
    const totalDots = Math.ceil(file.lines.length / linesPerDot);
    const availableWidth = width - dotsColumnX;
    const maxDotsPerRow = Math.floor(availableWidth / approxDotWidth) || totalDots;
    const dotRows = Math.ceil(totalDots / maxDotsPerRow);
    return { ...file, groupHeight: fileInfoHeight + dotRows * dotRowHeight };
  });

  $: positions = (() => {
    let pos = [], y = 0;
    for (const f of filesWithHeights) {
      pos.push(y);
      y += f.groupHeight;
    }
    return pos;
  })();

  $: if (svg) {
    const rowHeight = 50;
    const svgWidth = 0.8*width;
    const totalHeight = positions.length
      ? positions[positions.length - 1] + filesWithHeights[filesWithHeights.length - 1].groupHeight
      : 0;
    d3.select(svg)
      .attr('width', svgWidth)
      .attr('height', totalHeight)
      .style('overflow', 'hidden');

    const groups = d3.select(svg)
      .selectAll('g.file')
      .data(files, d => d.name)

    groups.exit().remove();

    const enterGroups = groups.enter()
      .append('g')
      .attr('class', 'file')
      .attr('transform', (d, i) => `translate(0, ${positions[i]})`);

    enterGroups.append('text')
      .attr('class', 'filename')
      .attr('x', 10)
      .attr('y', rowHeight / 2)
      .attr('dominant-baseline', 'hanging')
      .style('font-size', '0.7em')
      .text(d => d.name);

    enterGroups.append('text')
      .attr('class', 'linecount')
      .attr('x', 10)
      .attr('y', rowHeight / 2 + 12)
      .attr('dominant-baseline', 'hanging')
      .style('font-size', '0.7em')
      .text(d => `${d.lines.length} lines`);

    enterGroups.append('text')
      .attr('class', 'unit-dots no-fade')
      .attr('x', dotsColumnX)
      .attr('y', baseY - 2)
      .attr('dominant-baseline', 'mathematical')
      .attr('fill', "#1f77b4")
      .html(d => generateDots(d, svgWidth));

    // Update existing groups
    groups
      .transition()
      .attr('transform', (d, i) => `translate(0, ${positions[i]})`)
      .duration(1000)
      // .duration(function(d, i) {
      //   const currentTransform = this.getAttribute("transform") || "translate(0,0)";
      //   const match = currentTransform.match(/translate\(\s*0\s*,\s*([0-9.]+)\s*\)/);
      //   const oldY = match ? +match[1] : 0;
      //   const newY = positions[i];
      //   const distance = Math.abs(newY - oldY);
      //   return distance * 2;
      // })
      .select('text.filename')
      .text(d => d.name);

    groups
      .select('text.linecount')
      .text(d => `${d.lines.length} lines`)
      .attr('x', 10)
      .attr('y', rowHeight / 2 + 12);

    groups
      .select('text.unit-dots')
      .attr('class', 'unit-dots no-fade')
      .html(d => generateDots(d, svgWidth))
      .attr('x', dotsColumnX)
      .attr('fill', "#1f77b4");

    groups.each(function(d) {
      const groupSel = d3.select(this);
      const unitDotsSel = groupSel.select('text.unit-dots');
      const newCount = d.lines.length;
      const oldCount = previousDotCounts.get(d.name) || 0;
      
      unitDotsSel.html(generateDots(d, svgWidth));
      
      if(newCount > oldCount) {
        unitDotsSel.selectAll('tspan.dot')
          .filter(function() {
            return +this.getAttribute('data-index') >= oldCount;
          })
          .style('opacity', 0)
          .style('transform', 'scale(0)')
          .transition()
          .duration(1000)
          .ease(d3.easeCubicOut)
          .style('opacity', 1)
          .style('transform', 'scale(1)')
      }
      
      previousDotCounts.set(d.name, newCount);
    });

  }


</script>

<svg bind:this={svg} />