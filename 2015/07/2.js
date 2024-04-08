"use strict";
const fs = require("node:fs");
const parse = require("./parse");
const calculateSignal = require("./calculateSignal");
let contents = fs.readFileSync("./2015/07/input.txt", "utf8").toString();

let instructions = parse(contents);
const a = calculateSignal(instructions, "a");

for (let key in instructions) {
  instructions[key].state = undefined;
}

instructions["b"] = {
  state: "CALCULATED",
  calculatedValue: a,
};

console.log(calculateSignal(instructions, "a"));
