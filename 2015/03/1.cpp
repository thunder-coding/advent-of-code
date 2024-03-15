#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stdint.h>
#include <stdlib.h>

struct Coordinate {
  int16_t x;
  int16_t y;
};

bool operator<(const Coordinate &a, const Coordinate &b) {
  return *(uint32_t *)&a < *(uint32_t *)&b;
}

int main() {
  auto input = std::ifstream("./2015/03/input.txt");
  if (!input.good()) {
    std::cerr << "Error opening file './2015/03/input.txt'" << std::endl;
    return EXIT_FAILURE;
  }
  Coordinate position = {
      .x = 0,
      .y = 0,
  };
  std::map<Coordinate, unsigned int> houses = {};
  houses[position] = 1;
  int ch;
  while ((ch = input.get()) != EOF) {
    switch (ch) {
    case '^':
      position.y++;
      break;
    case 'v':
      position.y--;
      break;
    case '>':
      position.x++;
      break;
    case '<':
      position.x--;
      break;
    default:
      std::cerr << "Unexpected character in input.txt" << std::endl;
      return EXIT_FAILURE;
    }
    auto house = houses.find(position);
    if (house == houses.end()) {
      houses[position] = 1;
    } else {
      house->second++;
    }
  }
  std::cout << houses.size();
  return EXIT_SUCCESS;
}
