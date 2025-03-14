#include "parse.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>

auto Year2015::Day02::parse(const std::string& input) -> Boxes {
  Boxes boxes = {};
  Box box = {0, 0, 0};
  int sideIndex = 0;
  for (const auto& chr : input) {
    switch (chr) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        box[sideIndex] *= 10;
        box[sideIndex] += chr - '0';
        break;
      case 'x':
        if (++sideIndex == 3) {
          throw std::runtime_error(
              "A cuboid is supposed to have only 3 sides on line " +
              std::to_string(boxes.size() + 1));
        }
        break;
      case '\n':
        if (sideIndex == 2) {
          sideIndex = 0;
          std::sort(box.begin(), box.end());
          boxes.push_back(box);
          for (size_t boxLengthIndex = 0; boxLengthIndex != 3;
               boxLengthIndex++) {
            box[boxLengthIndex] = 0;
          }
        } else {
          throw std::runtime_error("Expected three sides, found only " +
                                   std::to_string(sideIndex + 1) +
                                   " when parsing input.txt on line " +
                                   std::to_string(boxes.size() + 1));
        }
        break;
      default:
        throw std::runtime_error("Unexpected character at line " +
                                 std::to_string(boxes.size() + 1) +
                                 " when parsing input.txt");
        break;
    }
  }

  // Deal with non-newline endings gracefully
  if (sideIndex == 0) {
  } else if (sideIndex == 2) {
    std::sort(box.begin(), box.end());
    boxes.push_back(box);
  } else {
    throw std::runtime_error(
        "Expected three sides, found only " + std::to_string(sideIndex + 1) +
        " when parsing input.txt on line " + std::to_string(boxes.size() + 1));
  }
  return boxes;
}