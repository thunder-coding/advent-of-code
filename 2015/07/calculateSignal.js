function calculateSignal(instructions, wireId) {
  let wire = instructions[wireId];
  if (wire === undefined) {
    throw new Error("Wire not found in the circuit");
  }
  switch (wire.state) {
    case "CALCULATING":
      throw new Error(
        `Recursion detected whle calculating signal for ${wireId}`,
      );
    case "CALCULATED":
      return wire.calculatedValue;
  }
  wire.state = "CALCULATING";
  let a = wire.a,
    b = wire.b;
  if (typeof a === "string") {
    a = calculateSignal(instructions, a);
  }
  if (typeof b === "string") {
    b = calculateSignal(instructions, b);
  }
  switch (wire.gate) {
    case "COPY":
      wire.calculatedValue = a;
      break;
    case "AND":
      wire.calculatedValue = a & b;
      break;
    case "OR":
      wire.calculatedValue = a | b;
      break;
    case "NOT":
      wire.calculatedValue = ~a & 0x0000fffff;
      break;
    case "LSHIFT":
      wire.calculatedValue = (a << b) & 0x0000ffff;
      break;
    case "RSHIFT":
      wire.calculatedValue = a >> b;
      break;
    default:
      throw new Error(`Unknown gate found '${wire.gate}'`);
  }
  wire.state = "CALCULATED";
  return wire.calculatedValue;
}
module.exports = calculateSignal;
