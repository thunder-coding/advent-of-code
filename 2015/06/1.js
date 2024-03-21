"use strict";
const fs = require("node:fs");
let contents = fs.readFileSync("./2015/06/input.txt", "utf8").toString();

class Lightgrid {
  lights = undefined;
  constructor() {
    this.lights = [];
    for (let x = 0; x != 1000; x++) {
      this.lights[x] = [];
      for (let y = 0; y != 1000; y++) {
        this.lights[x][y] = false;
      }
    }
  }

  turnOn(begx, begy, endx, endy) {
    let stepx = begx < endx ? +1 : -1;
    let stepy = begy < endy ? +1 : -1;
    for (let x = begx; x != endx + stepx; x += stepx) {
      for (let y = begy; y != endy + stepy; y += stepy) {
        this.lights[x][y] = true;
      }
    }
  }
  turnOff(begx, begy, endx, endy) {
    let stepx = begx < endx ? +1 : -1;
    let stepy = begy < endy ? +1 : -1;
    for (let x = begx; x != endx + stepx; x += stepx) {
      for (let y = begy; y != endy + stepy; y += stepy) {
        this.lights[x][y] = false;
      }
    }
  }

  toggle(begx, begy, endx, endy) {
    let stepx = begx < endx ? +1 : -1;
    let stepy = begy < endy ? +1 : -1;
    for (let x = begx; x != endx + stepx; x += stepx) {
      for (let y = begy; y != endy + stepy; y += stepy) {
        this.lights[x][y] = !this.lights[x][y];
      }
    }
  }

  countOn() {
    let count = 0;
    for (let x = 0; x != 1000; x++) {
      for (let y = 0; y != 1000; y++) {
        if (this.lights[x][y]) {
          count++;
        }
      }
    }
    return count;
  }
}

let lightgrid = new Lightgrid();
for (const line of contents.split("\n")) {
  let { instruction, begx, begy, endx, endy } = line.match(
    /^(?<instruction>turn on|turn off|toggle) (?<begx>[0-9]+),(?<begy>[0-9]+) through (?<endx>[0-9]+),(?<endy>[0-9]+)$/,
  ).groups;
  begx = Number(begx);
  begy = Number(begy);
  endx = Number(endx);
  endy = Number(endy);
  switch (instruction) {
    case "turn on":
      lightgrid.turnOn(begx, begy, endx, endy);
      break;
    case "turn off":
      lightgrid.turnOff(begx, begy, endx, endy);
      break;
    case "toggle":
      lightgrid.toggle(begx, begy, endx, endy);
      break;
  }
}
console.log(lightgrid.countOn());
