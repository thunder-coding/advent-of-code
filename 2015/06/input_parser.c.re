#include "input_parser.h"

#include <stdbool.h>
#include <stdio.h>

static inline bool parse_coordinates(FILE *input, int *x, int *y) {
  int ch;
  int *curr = x;
  *x = *y = 0;
  while (true) {
    ch = fgetc(input);
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
      if (curr == x) {
        curr = y;
      } else {
        return false;
      }
      break;
    case ' ':
    case '\n':
      ungetc(ch, input);
      return true;
    case EOF:
      if (curr == y) {
        return true;
      }
      break;
    default:
      return false;
    }
  }
}

void Parse_instruction(FILE *input, struct Instruction *instruction) {
  long int mar;
  /*!re2c
    re2c:api = custom;
    re2c:api:style = free-form;
    re2c:define:YYCTYPE = "char";
    re2c:define:YYPEEK = "fgetc(input); ungetc(yych, input)";
    re2c:define:YYSKIP = "fseek(input, 1, SEEK_CUR);";
    re2c:define:YYBACKUP = "mar = ftell(input);";
    re2c:define:YYRESTORE = "fseek(input, mar, SEEK_SET);";
    re2c:define:YYLESSTHAN = "feof(input)";
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    * {
      instruction->action = Error;
      return;
    }
    $ {
      instruction->action = Eof;
      return;
    }
    "turn on" {
      instruction->action = TurnOn;
      goto after_instruction;
    }
    "turn off" {
      instruction->action = TurnOff;
      goto after_instruction;
    }
    "toggle" {
      instruction->action = Toggle;
      goto after_instruction;
    }
  */
after_instruction:
  // Eat whitespace
  if (fgetc(input) != ' ') {
    instruction->action = Error;
    return;
  }
  if (!parse_coordinates(input, &instruction->startx, &instruction->starty)) {
    instruction->action = Error;
    return;
  }
  // Eat whitespace
  if (fgetc(input) != ' ') {
    instruction->action = Error;
    return;
  }
  /*!re2c
    re2c:api = custom;
    re2c:api:style = free-form;
    re2c:define:YYCTYPE = "char";
    re2c:define:YYPEEK = "fgetc(input); ungetc(yych, input)";
    re2c:define:YYSKIP = "fseek(input, 1, SEEK_CUR);";
    re2c:define:YYBACKUP = "mar = ftell(input);";
    re2c:define:YYRESTORE = "fseek(input, mar, SEEK_SET);";
    re2c:define:YYLESSTHAN = "feof(input)";
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    * {
      instruction->action = Error;
      return;
    }
    $ {
      instruction->action = Eof;
      return;
    }
    "through" { goto after_through; }
  */
after_through:
  // Eat whitespace
  if (fgetc(input) != ' ') {
    instruction->action = Error;
    return;
  }
  if (!parse_coordinates(input, &instruction->endx, &instruction->endy)) {
    instruction->action = Error;
    return;
  }
  switch (fgetc(input)) {
  case '\n':
  case EOF:
    return;
  default:
    instruction->action = Error;
    return;
  }
}
