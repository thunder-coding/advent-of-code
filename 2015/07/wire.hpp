#ifndef ADVENT_OF_CODE_2020_07_WIRE_H
#define ADVENT_OF_CODE_2020_07_WIRE_H

#include "parser.hpp"
#include <cstdint>
#include <map>
#include <string>

enum class WireStatus {
  NotCalculated,
  Calculated,
  Calculating,
};

struct Wire {
  WireStatus status;
  uint16_t calculatedValue;
  Gate gate;
  Signal a, b;
};

using Wires = std::map<std::string, Wire>;

bool getWires(Wires &wires, std::ifstream &input);

bool calculateWire(Wires &wires, std::string, uint16_t &value);
#endif
