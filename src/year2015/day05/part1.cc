#include <string>

#include "../solutions.h"

auto Year2015::Day05::Part1(const std::string& input) -> std::string {
  bool has_twice_letters = false;
  bool has_naughty_pair = false;
  unsigned int vowel_count = 0;
  unsigned int nice_count = 0;
  for (size_t index = 0, last_newline_index = 0;
       index < input.size(); index++) {
    switch (input[index]) {
      case '\n':
        if (vowel_count >= 3 && has_twice_letters && !has_naughty_pair) {
          nice_count++;
        }
        last_newline_index = index;
        vowel_count = 0;
        has_twice_letters = false;
        has_naughty_pair = false;
        break;
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        vowel_count++;
      default:
        if (index > last_newline_index + 1) {
          if (input[index] == input[index - 1]) {
            has_twice_letters = true;
          }
          switch (input[index]) {
            case 'b':
            case 'd':
            case 'q':
            case 'y':
              if (input[index] - 1 == input[index - 1]) {
                has_naughty_pair = true;
              }
              break;
            default:
              break;
          }
        }
    }
  }
  // Handle the last string
  if (vowel_count >= 3 && has_twice_letters && !has_naughty_pair) {
    nice_count++;
  }
  return std::to_string(nice_count);
}