#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>

#include "../solutions.h"

static inline auto hash(char chr1, char chr2) -> uint16_t {
  uint32_t returned = chr2;
  returned += (static_cast<uint16_t>(chr1) << 8);
  return returned;
}

auto Year2015::Day05::Part2(const std::string& input) -> std::string {
  bool has_repeating_pair = false;
  bool has_repeat_with_sep = false;
  unsigned int nice_count = 0;
  std::unordered_map<uint16_t, size_t> pairs;
  for (size_t index = 0, last_newline_index = 0; index < input.size();
       index++) {
    switch (input[index]) {
      case '\n':
        if (has_repeat_with_sep && has_repeating_pair) {
          nice_count++;
        }
        has_repeating_pair = false;
        has_repeat_with_sep = false;
        pairs.clear();
        last_newline_index = index;
        break;
      default:
        if (index >= last_newline_index + 2) {
          const auto& find = pairs.find(hash(input[index], input[index - 1]));
          if (find != pairs.end()) {
            if(find->second <= index - 2) {
              has_repeating_pair = true;
            }
          } else {
            pairs.emplace(hash(input[index], input[index - 1]), index);
          }
        }
        if (index >= last_newline_index + 3 &&
            input[index] == input[index - 2]) {
          has_repeat_with_sep = true;
        }
    }
  }
  // Handle the last string
  if (has_repeat_with_sep && has_repeating_pair) {
    nice_count++;
  }
  return std::to_string(nice_count);
}