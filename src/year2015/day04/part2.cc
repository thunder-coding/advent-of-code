#include <string>

#include "../../helpers/md5.h"
#include "../solutions.h"

auto Year2015::Day04::Part2(const std::string& input) -> std::string {
  std::string str;
  str.reserve(input.length() + 8);
  for (uint64_t i = 0;; i++) {
    Helpers::MD5 hasher;
    str = input + std::to_string(i);
    hasher.consume(std::vector<uint8_t>(str.begin(), str.end()));
    const auto hash = hasher.compute();
    if (hash[0] == 0x00 && hash[1] == 0x00 && hash[2] == 0x00) {
      return std::to_string(i);
    }
  }
}