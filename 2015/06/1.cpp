#include "input_parser.hpp"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>

class Lightgrid {
  bool lights[1000][1000];

public:
  Lightgrid() {
    for (int x = 0; x < 1000; x++) {
      for (int y = 0; y < 1000; y++) {
        this->lights[x][y] = false;
      }
    }
  }

  void turnon(const int startx, const int starty, const int endx,
              const int endy) {
    const int stepx = (startx < endx) ? +1 : -1;
    const int stepy = (starty < endy) ? +1 : -1;
    for (int x = startx; x != (endx + stepx); x += stepx) {
      for (int y = starty; y != (endy + stepy); y += stepy) {
        this->lights[x][y] = true;
      }
    }
  }
  void turnoff(const int startx, const int starty, const int endx,
               const int endy) {
    const int stepx = (startx < endx) ? +1 : -1;
    const int stepy = (starty < endy) ? +1 : -1;
    for (int x = startx; x != (endx + stepx); x += stepx) {
      for (int y = starty; y != (endy + stepy); y += stepy) {
        this->lights[x][y] = false;
      }
    }
  }
  void toggle(const int startx, const int starty, const int endx,
              const int endy) {
    const int stepx = (startx < endx) ? +1 : -1;
    const int stepy = (starty < endy) ? +1 : -1;
    for (int x = startx; x != (endx + stepx); x += stepx) {
      for (int y = starty; y != (endy + stepy); y += stepy) {
        this->lights[x][y] = !this->lights[x][y];
      }
    }
  }

  uint32_t counton() {
    uint32_t count = 0;
    for (int x = 0; x < 1000; x++) {
      for (int y = 0; y < 1000; y++) {
        if (this->lights[x][y])
          count++;
      }
    }
    return count;
  }
};

int main() {
  auto input = std::ifstream("./2015/06/input.txt");
  if (!input.good()) {
    std::cerr << "Error opening file './2015/06/input.txt'" << std::endl;
    return EXIT_FAILURE;
  }
  Lightgrid lightgrid;
  Instruction instruction;
  while (true) {
    Parse_instruction(input, instruction);
    switch (instruction.action) {
    case Action::Error:
      std::cerr << "Error parsing input file" << std::endl;
      return EXIT_FAILURE;
    case Action::Eof:
      goto end;
    case Action::TurnOn:
      lightgrid.turnon(instruction.startx, instruction.starty, instruction.endx,
                       instruction.endy);
      break;
    case Action::TurnOff:
      lightgrid.turnoff(instruction.startx, instruction.starty,
                        instruction.endx, instruction.endy);
      break;
    case Action::Toggle:
      lightgrid.toggle(instruction.startx, instruction.starty, instruction.endx,
                       instruction.endy);
      break;
    }
  }
end:
  std::cout << lightgrid.counton();
}
