#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "../solutions.h"

auto Year2015::Day01::Part1(const std::string& input) -> std::string {
  int floor = 0;
  for (const auto& chr : input) {
    switch (chr) {
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
  }
  return std::to_string(floor);
}