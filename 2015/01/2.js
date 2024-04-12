"use strict";
const fs = require("node:fs");
let contents = fs.readFileSync("./2015/01/input.txt", "utf8").toString();

let floor = 0;
let count = 0;
for (let character of contents) {
  count++;
  if (character == "(") {
    floor++;
  } else if (character == ")") {
    floor--;
  } else {
    console.warn(`Invalid character '${character}' in input file`);
  }
  if (floor == -1) {
    console.log(count);
    process.exit(0);
  }
}

console.error("Santa will never reach the basement");
