project(AdventOfCode)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(AOCSolutionLib SHARED
  src/year2015/day01/part1.cc
  src/year2015/day01/part2.cc
  src/year2015/day02/part1.cc
  src/year2015/day02/part2.cc
  src/year2015/day02/parse.cc
)

add_executable(AOC
  src/main.cc
)

add_executable(AOCTests
  src/tests/main.cc
)

target_link_libraries(AOC AOCSolutionLib)
target_link_libraries(AOCTests AOCSolutionLib)