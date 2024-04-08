#ifndef ADVENT_OF_CODE_2020_07_PARSER_HPP
#define ADVENT_OF_CODE_2020_07_PARSER_HPP

#include <cstdint>
#include <fstream>
#include <string>
#include <utility>
enum class Gate { And, Or, Not, LShift, RShift, Copy };
enum class SignalType { Raw, SignalFromWire };

struct Signal {
  SignalType type = SignalType::Raw;
  union {
    uint16_t raw;
    std::string wire;
  };
  // std::string constructor must be called manually
  inline Signal() {}
  inline ~Signal() {
    if (this->type == SignalType::SignalFromWire) {
      this->wire.~basic_string();
    }
  }
  inline Signal(const Signal &s) {
    this->type = s.type;
    if (s.type == SignalType::Raw) {
      this->raw = s.raw;
    } else {
      new (&this->wire) std::string(s.wire);
    }
  }
  inline Signal &operator=(const Signal &s) {
    this->type = s.type;
    if (s.type == SignalType::Raw) {
      this->raw = s.raw;
    } else {
      new (&this->wire) std::string(s.wire);
    }
    return *this;
  }
};

struct Instruction {
  Gate gate;
  Signal a, b, c;
};

enum class ParserError {
  NoError,
  Eof,
  ParsingError,
};

using ParserOutput = std::pair<ParserError, Instruction>;

ParserOutput parseInstruction(std::ifstream &input);

#endif
