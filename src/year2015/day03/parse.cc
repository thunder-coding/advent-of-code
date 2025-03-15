#include "parse.h"

#include <stdexcept>
#include <string>
auto Year2015::Day03::parse(const std::string& input) -> Directions {
  Directions directions;
  directions.reserve(input.size());
  for (const auto& chr : input) {
    switch (chr) {
      case '^': {
        directions.emplace_back(Direction::North);
        break;
      }
      case 'v': {
        directions.emplace_back(Direction::South);
        break;
      }
      case '<': {
        directions.emplace_back(Direction::West);
        break;
      }
      case '>': {
        directions.emplace_back(Direction::East);
        break;
      }
      default: {
        throw std::runtime_error("Unexpected character '" +
                                 std::to_string(chr) +
                                 "' when parsing input.txt");
      }
    }
  }
  return directions;
}