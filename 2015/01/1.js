"use strict";
const fs = require("node:fs");
let contents = fs.readFileSync("./2015/01/input.txt", "utf8").toString();

let floor = 0;
for (let character of contents) {
  if (character == "(") {
    floor++;
  } else if (character == ")") {
    floor--;
  } else {
    console.warn(`Invalid character '${character}' in input file`);
  }
}

console.log(floor);
