#include <cstdint>
#include <string>

#include "../solutions.h"
#include "parse.h"

auto Year2015::Day02::Part1(const std::string& input) -> std::string {
  auto boxes = parse(input);
  uint32_t wrappingPaperRequired = 0;
  for (const auto& box : boxes) {
    wrappingPaperRequired +=
        (3 * box[0] * box[1] + 2 * box[2] * (box[0] + box[1]));
  }
  return std::to_string(wrappingPaperRequired);
}