#include "common.h"
auto Year2015::Day03::operator<(const Coordinate &lhs, const Coordinate &rhs)
    -> bool {
  if (lhs.x == rhs.x) {
    return lhs.y < rhs.y;
  }
  return lhs.x < rhs.x;
}