#ifndef ADVENT_OF_CODE_2015_07_PARSER_H
#define ADVENT_OF_CODE_2015_07_PARSER_H

#include <stdint.h>
#include <stdio.h>

enum Gate {
  And,
  Or,
  Not,
  Lshift,
  Rshift,
  Copy,
  ParsingError,
  Eof,
};

enum SignalType { Raw, SignalFromWire };

union RawSignal {
  uint16_t raw;
  char wireId[2];
};

struct Signal {
  enum SignalType type;
  union RawSignal raw;
};

struct Instruction {
  enum Gate gate;
  // a & b are the inputs, and c is the destination
  struct Signal a, b, c;
};

struct Instruction parseInstruction(FILE *input);
#endif
