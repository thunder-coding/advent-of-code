const notRegex = /^NOT (?<a>[a-z]+|[0-9]+) -> (?<dest>[a-z]+)$/;
const copyRegex = /^(?<a>[a-z]+|[0-9]+) -> (?<dest>[a-z]+)$/;
const binaryRegex =
  /^(?<a>[a-z]+|[0-9]+) (?<gate>AND|OR|RSHIFT|LSHIFT) (?<b>[a-z]+|[0-9]+) -> (?<dest>[a-z]+)$/;

const UINT16_MAX = 2 ** 16 - 1;

function signal(source) {
  const raw = Number(source);
  if (isNaN(raw)) {
    return source;
  }
  if (raw > UINT16_MAX) {
    throw new Error(`signal size cannot exceed UINT16_MAX ${UINT16_MAX}`);
  }
  return raw;
}

function parseInstruction(line) {
  const notMatch = line.match(notRegex);
  if (notMatch != null) {
    return {
      gate: "NOT",
      a: signal(notMatch.groups.a),
      destination: notMatch.groups.dest,
    };
  }
  const copyMatch = line.match(copyRegex);
  if (copyMatch != null) {
    return {
      gate: "COPY",
      a: signal(copyMatch.groups.a),
      destination: copyMatch.groups.dest,
    };
  }
  const binaryMatch = line.match(binaryRegex);
  if (binaryMatch != null) {
    return {
      gate: binaryMatch.groups.gate,
      a: signal(binaryMatch.groups.a),
      b: signal(binaryMatch.groups.b),
      destination: binaryMatch.groups.dest,
    };
  }
  throw new Error(`Error parsing line: '${line}'`);
}

module.exports = parseInstruction;
