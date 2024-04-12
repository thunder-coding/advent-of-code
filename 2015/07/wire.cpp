#include "wire.hpp"
#include "parser.hpp"
#include <cstdint>
#include <iostream>
bool getWires(Wires &wires, std::ifstream &input) {
  ParserOutput instruction;
  for (int i = 1; true; i++) {
    instruction = parseInstruction(input);
    switch (instruction.first) {
    case ParserError::NoError:
      break;
    case ParserError::Eof:
      return true;
    case ParserError::ParsingError:
      std::cerr << "Error parsing instruction on line " << i << std::endl;
      return false;
    }
    auto wire = wires.find(instruction.second.c.wire);
    if (wire != wires.end()) {
      std::cerr << "Error a wire can recieve signal from only 1 source"
                << std::endl;
      return EXIT_FAILURE;
    }
    const Wire newWire = {
        .status = WireStatus::NotCalculated,
        .calculatedValue =
            0, // Silence Clang 18 error (-Wmissing-field-initializers)
        .gate = instruction.second.gate,
        .a = instruction.second.a,
        .b = instruction.second.b};
    wires[instruction.second.c.wire] = newWire;
  }
}

bool calculateWire(Wires &wires, std::string wireId, uint16_t &value) {
  auto wire = wires.find(wireId);
  if (wire == wires.end()) {
    std::cerr << "Wire not found in the circuit" << std::endl;
    return false;
  }
  switch (wire->second.status) {
  case WireStatus::Calculated:
    value = wire->second.calculatedValue;
    return true;
  case WireStatus::Calculating:
    std::cerr << "Recursion detected.. Aborting" << std::endl;
    return true;
  case WireStatus::NotCalculated:
    break;
  }
  wire->second.status = WireStatus::Calculating;
  uint16_t a, b;
  switch (wire->second.gate) {
  case Gate::And:
  case Gate::Or:
  case Gate::LShift:
  case Gate::RShift:
    if (wire->second.b.type == SignalType::SignalFromWire) {
      if (!calculateWire(wires, wire->second.b.wire, b)) {
        return false;
      }
    } else {
      b = wire->second.b.raw;
    }
  case Gate::Not:
  case Gate::Copy:
    if (wire->second.a.type == SignalType::SignalFromWire) {
      if (!calculateWire(wires, wire->second.a.wire, a)) {
        return false;
      }
    } else {
      a = wire->second.a.raw;
    }
  }
  switch (wire->second.gate) {
  case Gate::Not:
    value = ~a;
    break;
  case Gate::And:
    value = a & b;
    break;
  case Gate::Or:
    value = a | b;
    break;
  case Gate::LShift:
    value = a << b;
    break;
  case Gate::RShift:
    value = a >> b;
    break;
  case Gate::Copy:
    value = a;
    break;
  }
  wire->second.calculatedValue = value;
  wire->second.status = WireStatus::Calculated;
  return true;
}
