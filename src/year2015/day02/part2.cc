#include <cstdint>
#include <string>

#include "../solutions.h"
#include "parse.h"

auto Year2015::Day02::Part2(const std::string& input) -> std::string {
  auto boxes = parse(input);
  uint32_t ribbonLength = 0;
  for (const auto& box : boxes) {
    ribbonLength += (2 * (box[0] + box[1]) + box[0] * box[1] * box[2]);
  }
  return std::to_string(ribbonLength);
}