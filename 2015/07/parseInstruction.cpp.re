#include <fstream>
#include <limits>
#include <string>

#include "parser.hpp"
using SignalOutput = std::pair<ParserError, Signal>;

inline SignalOutput parseSignal(std::ifstream &input) {
  SignalOutput output;
  std::streampos mar;
  std::string str;
  // Default to raw signal so that destructor doesn't try to delete a string
  // that hasn't been initialized
  output.second.type = SignalType::Raw;
  /*!re2c
    re2c:api = custom;
    re2c:api:style = free-form;
    re2c:define:YYCTYPE = "char";
    re2c:define:YYPEEK = "input.peek();";
    re2c:define:YYSKIP = "{ input.ignore(); str += yych; }";
    re2c:define:YYBACKUP = "mar = input.tellg();";
    re2c:define:YYRESTORE = "input.seekg(mar);";
    re2c:define:YYLESSTHAN = "input.eof()";
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    [a-z]+ {
      output.first = ParserError::NoError;
      output.second.type = SignalType::SignalFromWire;
      new (&output.second.wire)std::string(str);
      return output;
    }
    [0-9]+ {
      uint32_t value = 0;
      for (size_t i = 0; i != str.size(); i++) {
        value *= 10;
        value += (str[i] - '0');
        if(value > std::numeric_limits<uint16_t>::max()) {
          output.first = ParserError::ParsingError;
          return output;
        }
      }
      output.first = ParserError::NoError;
      output.second.type = SignalType::Raw;
      output.second.raw = value;
      return output;
    }
    * {
      output.first = ParserError::ParsingError;
      return output;
    }
    $ {
      output.first = ParserError::Eof;
      return output;
    }
  */
}

using GateOutput = std::pair<ParserError, Gate>;

inline GateOutput parseGate(std::ifstream &input) {
  GateOutput output;
  std::streampos mar;
  std::string str;
  /*!re2c
    re2c:api = custom;
    re2c:api:style = free-form;
    re2c:define:YYCTYPE = "char";
    re2c:define:YYPEEK = "input.peek();";
    re2c:define:YYSKIP = "{ input.ignore(); str += yych; }";
    re2c:define:YYBACKUP = "mar = input.tellg();";
    re2c:define:YYRESTORE = "input.seekg(mar);";
    re2c:define:YYLESSTHAN = "input.eof()";
    re2c:yyfill:enable = 0;
    re2c:eof = 0;

    "AND" {
      output.first = ParserError::NoError;
      output.second = Gate::And;
      return output;
    }
    "OR" {
      output.first = ParserError::NoError;
      output.second = Gate::Or;
      return output;
    }
    "NOT" {
      output.first = ParserError::NoError;
      output.second = Gate::Not;
      return output;
    }
    "LSHIFT" {
      output.first = ParserError::NoError;
      output.second = Gate::LShift;
      return output;
    }
    "RSHIFT" {
      output.first = ParserError::NoError;
      output.second = Gate::RShift;
      return output;
    }
    * {
      output.first = ParserError::ParsingError;
      return output;
    }
    $ {
      output.first = ParserError::Eof;
      return output;
    }
  */
}

ParserOutput parseInstruction(std::ifstream &input) {
  ParserOutput out;
  auto gate = parseGate(input);
  SignalOutput signal;
  switch (gate.first) {
  case ParserError::NoError:
    // If the first token is a gate, then it's supposed to be a 'NOT' gate
    switch (gate.second) {
    case Gate::Not:
      // Eat the whitespace
      out.second.gate = Gate::Not;
      if (input.get() != ' ') {
        out.first = ParserError::ParsingError;
        return out;
      }
      // get the actual signal after the 'NOT' gate
      signal = parseSignal(input);
      if (signal.first != ParserError::NoError) {
        out.first = signal.first;
        return out;
      }
      out.second.a = signal.second;
      // Eat the whitespace
      if (input.get() != ' ') {
        out.first = ParserError::ParsingError;
        return out;
      }
      break;
    default:
      out.first = ParserError::ParsingError;
      return out;
    }
    break;
  case ParserError::Eof:
    out.first = ParserError::Eof;
    return out;
  case ParserError::ParsingError:
    input.unget();
    // First token is not gate, then it must be a signal
    signal = parseSignal(input);
    if (signal.first != ParserError::NoError) {
      out.first = signal.first;
      return out;
    }
    out.second.a = signal.second;
    // Eat the whitesace
    if (input.get() != ' ') {
      out.first = ParserError::ParsingError;
      return out;
    }
    // Get the gate
    gate = parseGate(input);
    if (gate.first != ParserError::NoError) {
      input.unget();
      // Maybe it's a copy instruction
      out.second.gate = Gate::Copy;
      goto before_arrow;
    }
    out.second.gate = gate.second;
    // Eat the whitespace
    if (input.get() != ' ') {
      out.first = ParserError::ParsingError;
      return out;
    }
    // Get the second signal
    signal = parseSignal(input);
    if (signal.first != ParserError::NoError) {
      out.first = signal.first;
      return out;
    }
    out.second.b = signal.second;
    // Eat the whitespace
    if (input.get() != ' ') {
      out.first = ParserError::ParsingError;
      return out;
    }
    break;
  }
before_arrow:
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
      out.first = ParserError::ParsingError;
      return out;
    }
    $ {
      out.first = ParserError::ParsingError;
      return out;
    }
    "->" {
      goto after_arrow;
    }
  */
after_arrow:
  // Eat the whitespace
  if (input.get() != ' ') {
    out.first = ParserError::ParsingError;
    return out;
  }
  // Get the location
  signal = parseSignal(input);
  if (signal.first != ParserError::NoError) {
    out.first = signal.first;
    return out;
  }
  if (signal.second.type != SignalType::SignalFromWire) {
    out.first = ParserError::ParsingError;
    return out;
  }
  out.second.c = signal.second;
  // Eat the newline (may not exist if end of file)
  const int c = input.get();
  if (c != '\n' && c != EOF) {
    out.first = ParserError::ParsingError;
    return out;
  }
  out.first = ParserError::NoError;
  return out;
}
