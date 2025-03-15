#ifndef ADVENT_OF_CODE_SRC_YEAR2015_DAY03_COMMON_H
#define ADVENT_OF_CODE_SRC_YEAR2015_DAY03_COMMON_H
namespace Year2015::Day03 {
struct Coordinate {
  int x, y;
};
auto operator<(const Coordinate& lhs, const Coordinate& rhs) -> bool;
}  // namespace Year2015::Day03
#endif