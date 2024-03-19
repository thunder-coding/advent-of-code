#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
int main() {
  auto input = std::ifstream("./2015/05/input.txt");
  if (!input.good()) {
    std::cerr << "Error opening file './2015/04/input.txt'" << std::endl;
    return EXIT_FAILURE;
  }
  uint16_t niceCount = 0;
  std::string line;
  while (!input.eof()) {
    std::map<std::tuple<char, char>, size_t> pairs = {};
    input >> line;
    const size_t size = line.size();
    bool condition1 = false;
    bool condition2 = false;
    char prev2;
    char *pair = line.data();
    for (size_t index = 0; index + 1 < size; index++, prev2 = pair[0]) {
      pair = &((char *)line.data())[index];
      const auto tup = std::make_tuple(pair[0], pair[1]);
      const auto &f = pairs.find(tup);
      if (!condition1 && f != pairs.end() && f->second + 2 <= index) {
        condition1 = true;
      }
      if (!condition2 && (pair[1] == prev2) && (index != 0)) {
        condition2 = true;
      }
      if (condition1 && condition2) {
        goto nice;
      }
      if (!pairs.contains(tup))
        pairs[tup] = index;
    }
  naughtly:
    continue;
  nice:
    niceCount++;
  }
  std::cout << niceCount;
  return EXIT_SUCCESS;
}
