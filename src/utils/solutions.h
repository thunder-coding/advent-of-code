#ifndef ADVENT_OF_CODE_UTILS_SOLUTIONS_H
#define ADVENT_OF_CODE_UTILS_SOLUTIONS_H
#include <functional>
#include <map>
#include <string>

using Solution = std::function<std::string(const std::string&)>;

struct Problem {
  std::string inputFilePath;
  Solution solution;
  std::string answerFilePath;
};

using Problems = std::map<std::string, Problem>;

#define SOLUTION_FOR_DAY(year, day)                        \
  namespace Year##year {                                   \
    namespace Day##day {                                   \
      auto Part1(const std::string& input) -> std::string; \
      auto Part2(const std::string& input) -> std::string; \
    }                                                      \
  }

// clang-format off
#define REPEAT_FOR_ALL_DAYS(macro, ...) \
  macro(__VA_ARGS__, 01) \
  macro(__VA_ARGS__, 02) \
  macro(__VA_ARGS__, 03) \
  macro(__VA_ARGS__, 04) \
  macro(__VA_ARGS__, 05) \
  macro(__VA_ARGS__, 06) \
  macro(__VA_ARGS__, 07) \
  macro(__VA_ARGS__, 08) \
  macro(__VA_ARGS__, 09) \
  macro(__VA_ARGS__, 10) \
  macro(__VA_ARGS__, 11) \
  macro(__VA_ARGS__, 12) \
  macro(__VA_ARGS__, 13) \
  macro(__VA_ARGS__, 14) \
  macro(__VA_ARGS__, 15) \
  macro(__VA_ARGS__, 17) \
  macro(__VA_ARGS__, 18) \
  macro(__VA_ARGS__, 19) \
  macro(__VA_ARGS__, 20) \
  macro(__VA_ARGS__, 21) \
  macro(__VA_ARGS__, 22) \
  macro(__VA_ARGS__, 23) \
  macro(__VA_ARGS__, 24) \
  macro(__VA_ARGS__, 25)
// clang-format on

#define SOLUTION_FOR_YEAR(year) REPEAT_FOR_ALL_DAYS(SOLUTION_FOR_DAY, year)

#define SOLUTION_INITIALISERLIST_ELEMENT_FOR_DAY_PART(year, day, part) \
  {#year "/" #day "/" #part,                                           \
   {.inputFilePath = "src/year" #year "/day" #day "/input.txt",        \
    .solution = Year##year::Day##day::Part##part,                      \
    .answerFilePath = "src/year" #year "/day" #day "/answer" #part ".txt"}},

#define SOLUTION_INITIALISERLIST_FOR_DAY(year, day)           \
  SOLUTION_INITIALISERLIST_ELEMENT_FOR_DAY_PART(year, day, 1) \
  SOLUTION_INITIALISERLIST_ELEMENT_FOR_DAY_PART(year, day, 2)

#define SOLUTION_INITIALISERLIST_FOR_YEAR(year) \
  REPEAT_FOR_ALL_DAYS(SOLUTION_INITIALISERLIST_FOR_DAY, year, day)

#endif