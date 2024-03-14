"use strict";
const fs = require("node:fs");

const input = fs.readFileSync("./2015/02/input.txt", "utf8").toString();

let ribbonLength = 0;
for (const line of input.split("\n")) {
  if (line === "") continue;
  let sides = line
    .split("x")
    .map((side) => Number(side))
    .sort((a, b) => a - b);
  ribbonLength += sides[0] * sides[1] * sides[2] + 2 * (sides[0] + sides[1]);
}

console.log(ribbonLength);
