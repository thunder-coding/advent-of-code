"use strict";
const fs = require("node:fs");
let contents = fs.readFileSync("./2015/03/input.txt", "utf8").toString();

class Coordinate {
  x;
  y;
  constructor(x, y) {
    this.x = x;
    this.y = y;
  }
  toString() {
    return `(${this.x},${this.y})`;
  }
}

let santaPos = new Coordinate(0, 0);
let botPos = new Coordinate(0, 0);
let pos = botPos;
let housesWithGifts = new Set();
housesWithGifts.add(santaPos.toString());
for (let character of contents) {
  if (pos === botPos) pos = santaPos;
  else pos = botPos;
  switch (character) {
    case "^":
      pos.y++;
      break;
    case "v":
      pos.y--;
      break;
    case "<":
      pos.x--;
      break;
    case ">":
      pos.x++;
      break;
    default:
      console.error(`Unexpected character '${character}' in input file`);
      process.exit(1);
  }
  housesWithGifts.add(pos.toString());
}

console.log(housesWithGifts.size);
