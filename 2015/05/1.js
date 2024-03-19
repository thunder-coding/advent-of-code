"use strict";
const fs = require("node:fs");
const crypto = require("node:crypto");
let contents = fs.readFileSync("./2015/05/input.txt", "utf8").toString();

let niceCount = 0;
for (const line of contents.split("\n")) {
  if (
    /(.)\1/.test(line) &&
    /([aeiouAEIOU]).*?([aeiouAEIOU]).*?([aeiouAEIOU])/.test(line) &&
    !/ab|cd|pq|xy/.test(line)
  ) {
    niceCount++;
  }
}
console.log(niceCount);
