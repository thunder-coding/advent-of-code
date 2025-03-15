#ifndef ADVENT_OF_CODE_SRC_YEAR2015_DAY03_PARSE_h
#define ADVENT_OF_CODE_SRC_YEAR2015_DAY03_PARSE_h

#include <cstdint>
#include <string>
#include <vector>
namespace Year2015::Day03 {
enum class Direction : uint8_t {
  North,
  South,
  East,
  West,
};

using Directions = std::vector<Direction>;
auto parse(const std::string& input) -> Directions;
}  // namespace Year2015::Day03

#endif  // !ADVENT_OF_CODE_SRC_YEAR2015_DAY02_PARSE_h