#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <linux/limits.h>
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
  Coordinate botPosition = {
      .x = 0,
      .y = 0,
  };
  std::map<Coordinate, unsigned int> houses = {};
  houses[position] = 1;
  bool lastGiftBySanta = false;
  int ch;
  while ((ch = input.get()) != EOF) {
    Coordinate *pos;
    if (lastGiftBySanta)
      pos = &position;
    else
      pos = &botPosition;
    lastGiftBySanta = !lastGiftBySanta;
    switch (ch) {
    case '^':
      pos->y++;
      break;
    case 'v':
      pos->y--;
      break;
    case '>':
      pos->x++;
      break;
    case '<':
      pos->x--;
      break;
    default:
      std::cerr << "Unexpected character in input.txt" << std::endl;
      return EXIT_FAILURE;
    }
    auto house = houses.find(*pos);
    if (house == houses.end()) {
      houses[*pos] = 1;
    } else {
      house->second++;
    }
  }
  std::cout << houses.size();
  return EXIT_SUCCESS;
}
