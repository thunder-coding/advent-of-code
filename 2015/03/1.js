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
let housesWithGifts = new Set();
housesWithGifts.add(santaPos.toString());
for (let character of contents) {
  switch (character) {
    case "^":
      santaPos.y++;
      break;
    case "v":
      santaPos.y--;
      break;
    case "<":
      santaPos.x--;
      break;
    case ">":
      santaPos.x++;
      break;
    default:
      console.error(`Unexpected character '${character}' in input file`);
      process.exit(1);
  }
  housesWithGifts.add(santaPos.toString());
}

console.log(
  `${housesWithGifts.size} houses recieved atleast 1 gift from Santa`,
);
