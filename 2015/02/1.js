"use strict";
const fs = require("node:fs");

const input = fs.readFileSync("./2015/02/input.txt", "utf8").toString();

let area = 0;
for (const line of input.split("\n")) {
  if (line === "") continue;
  let sides = line
    .split("x")
    .map((side) => Number(side))
    .sort((a, b) => a - b);
  area += 3 * sides[0] * sides[1] + 2 * sides[2] * (sides[0] + sides[1]);
}

console.log(area);
