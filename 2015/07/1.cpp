#include "wire.hpp"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>

int main() {
  auto input = std::ifstream("./2015/07/input.txt");
  if (!input.good()) {
    std::cerr << "Error opening file './2015/07/input.txt'" << std::endl;
    return EXIT_FAILURE;
  }
  Wires wires;
  if (!getWires(wires, input)) {
    return EXIT_FAILURE;
  }
  uint16_t value;
  if (!calculateWire(wires, "a", value)) {
    return EXIT_FAILURE;
  }
  std::cout << value;
  return EXIT_SUCCESS;
}
