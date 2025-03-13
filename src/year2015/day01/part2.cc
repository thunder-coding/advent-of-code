#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "../solutions.h"

auto Year2015::Day01::Part2(const std::string& input) -> std::string {
  int floor = 0;
  for (size_t i = 0; i < input.size(); i++) {
    switch (input[i]) {
      case '(':
        floor++;
        break;
      case ')':
        floor--;
        break;
      default:
        throw std::runtime_error(
            "Invalid character encountered while reading input.txt");
    }
    if (floor == -1) {
      return std::to_string(i + 1);
    }
  }
  throw std::runtime_error("Santa never reached the basement");
}