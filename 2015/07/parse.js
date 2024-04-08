const parseInstruction = require("./parseInstruction");

function parse(contents) {
  let instructions = {};
  for (let line of contents.split("\n")) {
    let instruction = parseInstruction(line);
    if (instructions[instruction.destination] !== undefined) {
      throw new Error("a wire can only recieve signal from one source");
    }
    instructions[instruction.destination] = {
      gate: instruction.gate,
      a: instruction.a,
      b: instruction?.b,
    };
  }
  return instructions;
}

module.exports = parse;
