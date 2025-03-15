#include <set>
#include <string>

#include "../solutions.h"
#include "common.h"
#include "parse.h"

auto Year2015::Day03::Part1(const std::string& input) -> std::string {
  const auto directions = parse(input);
  Coordinate position = {.x = 0, .y = 0};
  std::set<Coordinate> houses = {position};
  for (const auto& direction : directions) {
    switch (direction) {
      case Direction::North: {
        position.y++;
        houses.insert(position);
        break;
      }
      case Direction::South: {
        position.y--;
        houses.insert(position);
        break;
      }
      case Direction::East: {
        position.x++;
        houses.insert(position);
        break;
      }
      case Direction::West: {
        position.x--;
        houses.insert(position);
        break;
      }
    }
  }
  return std::to_string(houses.size());
}