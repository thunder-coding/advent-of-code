#include "parser.h"

#include <stdbool.h>
#include <stdint.h>

static inline bool parseSignal(FILE *input, struct Signal *signal) {
  int ch;
  ch = fgetc(input);
  // It's a identifier (signal from wire)
  if (ch <= 'z' && ch >= 'a') {
    signal->type = SignalFromWire;
    signal->raw.wireId[0] = ch;
    ch = fgetc(input);
    if (ch <= 'z' && ch >= 'a') {
      signal->raw.wireId[1] = ch;
      ch = fgetc(input);
      return (ch == ' ' || ch == '\n' || ch == EOF);
    } else if (ch == ' ' || ch == '\n' || ch == EOF) {
      signal->raw.wireId[1] = '\0';
      return true;
    } else {
      return false;
    }
  } else if (ch <= '9' && ch >= '0') {
    signal->type = Raw;
    // We are using a larger integer type for parsing so that we can detect an
    // overflow (if any)
    uint32_t num = 0;
    do {
      if (num > UINT16_MAX) {
        return false;
      }
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
        num *= 10;
        num += (ch - '0');
        break;
      case ' ':
      case '\n':
      case EOF:
        signal->raw.raw = num;
        return true;
      default:
        return false;
      }
    } while ((ch = fgetc(input)) != EOF);
    return false;
  } else {
    return false;
  }
}

static inline enum Gate parseGate(FILE *input) {
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
      ungetc(yych, input);
      return ParsingError;
    }

    $ {
      return Eof;
    }

    "AND" " " {
      return And;
    }
    "OR" " " {
      return Or;
    }
    "NOT" " " {
      return Not;
    }
    "LSHIFT" " " {
      return Lshift;
    }
    "RSHIFT" " " {
      return Rshift;
    }
  */
}

struct Instruction parseInstruction(FILE *input) {
  struct Instruction op;
  long int mar;
  op.gate = parseGate(input);
  switch (op.gate) {
  case And:
  case Or:
  case Lshift:
  case Rshift:
    op.gate = ParsingError;
    return op;
  case Not: {
    if (!parseSignal(input, &op.a)) {
      op.gate = ParsingError;
      return op;
    }
  } break;
  case ParsingError: {
    if (!parseSignal(input, &op.a)) {
      op.gate = ParsingError;
      return op;
    }
    op.gate = parseGate(input);
    switch (op.gate) {
    case And:
    case Or:
    case Lshift:
    case Rshift:
      break;
    case ParsingError: {
      op.gate = Copy;
      goto before_parsing_destination_symbol;
    }
    default:
      op.gate = ParsingError;
      return op;
    }
    if (!parseSignal(input, &op.b)) {
      op.gate = ParsingError;
      return op;
    }
  } break;
  case Eof:
    op.gate = Eof;
    return op;
  default: {
    op.gate = ParsingError;
    return op;
  }
  }

before_parsing_destination_symbol:
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
      op.gate = ParsingError;
      return op;
    }
    $ {
      op.gate = ParsingError;
      return op;
    }
    "-> " {
      goto before_parsing_destination;
    }
  */
before_parsing_destination:
  if (!parseSignal(input, &op.c) || op.c.type != SignalFromWire) {
    op.gate = ParsingError;
    return op;
  }
  return op;
}
