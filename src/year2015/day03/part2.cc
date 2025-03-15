#include <set>
#include <string>

#include "../solutions.h"
#include "common.h"
#include "parse.h"

auto Year2015::Day03::Part2(const std::string& input) -> std::string {
  const auto directions = parse(input);
  Coordinate santaPos = {.x = 0, .y = 0};
  Coordinate roboSantaPos = {.x = 0, .y = 0};
  std::set<Coordinate> houses = {santaPos};
  // Start with robo santa as we are changing the current santa before looking
  // at the first instruction
  Coordinate* currentSantaPos = &roboSantaPos;
  for (const auto& direction : directions) {
    if (currentSantaPos == &santaPos) {
      currentSantaPos = &roboSantaPos;
    } else /* if (currentSantaPos == &roboSantaPos) */ {
      currentSantaPos = &santaPos;
    }
    switch (direction) {
      case Direction::North: {
        currentSantaPos->y++;
        houses.insert(*currentSantaPos);
        break;
      }
      case Direction::South: {
        currentSantaPos->y--;
        houses.insert(*currentSantaPos);
        break;
      }
      case Direction::East: {
        currentSantaPos->x++;
        houses.insert(*currentSantaPos);
        break;
      }
      case Direction::West: {
        currentSantaPos->x--;
        houses.insert(*currentSantaPos);
        break;
      }
    }
  }
  return std::to_string(houses.size());
}