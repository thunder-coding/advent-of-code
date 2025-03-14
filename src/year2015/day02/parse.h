#ifndef ADVENT_OF_CODE_SRC_YEAR2015_DAY02_PARSE_h
#define ADVENT_OF_CODE_SRC_YEAR2015_DAY02_PARSE_h

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace Year2015::Day02 {
using Side = uint32_t;
using Box = std::array<Side, 3>;
using Boxes = std::vector<Box>;

auto parse(const std::string& input) -> Boxes;
}  // namespace Year2015::Day02

#endif  // !ADVENT_OF_CODE_SRC_YEAR2015_DAY02_PARSE_h