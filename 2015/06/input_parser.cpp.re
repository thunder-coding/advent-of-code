#include "input_parser.hpp"

static inline bool parse_coordinates(std::ifstream &input, int &x, int &y) {
  int ch;
  int *curr = &x;
  x = y = 0;
  while (true) {
    ch = input.get();
    switch (ch) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *curr *= 10;
      *curr += (ch - '0');
      break;
    case ',':
      if (curr == &x) {
        curr = &y;
      } else {
        return false;
      }
      break;
    case ' ':
    case '\n':
      input.unget();
      return true;
    case EOF:
      if (curr == &y) {
        return true;
      }
      break;
    default:
      return false;
    }
  }
}

void Parse_instruction(std::ifstream &input, Instruction &instruction) {
  std::streampos mar;
  /*!re2c
    re2c:api = custom;
    re2c:api:style = free-form;
    re2c:define:YYCTYPE = "char";
    re2c:define:YYPEEK = "input.peek();";
    re2c:define:YYSKIP = "input.ignore();";
    re2c:define:YYBACKUP = "mar = input.tellg();";
    re2c:define:YYRESTORE = "input.seekg(mar);";
    re2c:define:YYLESSTHAN = "input.eof()";
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    * {
      instruction.action = Action::Error;
      return;
    }
    $ {
      instruction.action = Action::Eof;
      return;
    }
    "turn on" {
      instruction.action = Action::TurnOn;
      goto after_instruction;
    }
    "turn off" {
      instruction.action = Action::TurnOff;
      goto after_instruction;
    }
    "toggle" {
      instruction.action = Action::Toggle;
      goto after_instruction;
    }
  */
after_instruction:
  // Eat whitespace
  if (input.get() != ' ') {
    instruction.action = Action::Error;
    return;
  }
  if (!parse_coordinates(input, instruction.startx, instruction.starty)) {
    instruction.action = Action::Error;
    return;
  }
  // Eat whitespace
  if (input.get() != ' ') {
    instruction.action = Action::Error;
    return;
  }
  /*!re2c
    re2c:api = custom;
    re2c:api:style = free-form;
    re2c:define:YYCTYPE = "char";
    re2c:define:YYPEEK = "input.peek()";
    re2c:define:YYSKIP = "input.ignore();";
    re2c:define:YYBACKUP = "mar = input.tellg();";
    re2c:define:YYRESTORE = "input.seekg(mar);";
    re2c:define:YYLESSTHAN = "input.eof()";
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    * {
      instruction.action = Action::Error;
      return;
    }
    $ {
      instruction.action = Action::Eof;
      return;
    }
    "through" { goto after_through; }
  */
after_through:
  // Eat whitespace
  if (input.get() != ' ') {
    instruction.action = Action::Error;
    return;
  }
  if (!parse_coordinates(input, instruction.endx, instruction.endy)) {
    instruction.action = Action::Error;
    return;
  }
  switch (input.get()) {
  case '\n':
  case EOF:
    return;
  default:
    instruction.action = Action::Error;
    return;
  }
}
