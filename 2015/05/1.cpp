#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
int main() {
  auto input = std::ifstream("./2015/05/input.txt");
  if (!input.good()) {
    std::cerr << "Error opening file './2015/04/input.txt'" << std::endl;
    return EXIT_FAILURE;
  }
  uint16_t niceCount = 0;
  std::string line;
  while (!input.eof()) {
    input >> line;
    const size_t size = line.size();
    bool repeat = false;
    uint8_t vowelCount = 0;
    switch (line[0]) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      vowelCount++;
      break;
    }
    for (size_t index = 0; index + 1 < size; index++) {
      char *pair = &((char *)line.data())[index];
      if (!repeat && pair[0] == pair[1]) {
        repeat = true;
      }
      switch (pair[1]) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':
        vowelCount++;
        break;
      }
      if ((pair[0] == 'a' && pair[1] == 'b') ||
          (pair[0] == 'c' && pair[1] == 'd') ||
          (pair[0] == 'p' && pair[1] == 'q') ||
          (pair[0] == 'x' && pair[1] == 'y')) {
        goto naughtly;
      }
    }
    if (repeat && vowelCount >= 3) {
      niceCount++;
    }
  naughtly:; // Naughty string, do not increment counter
  }
  std::cout << niceCount;
  return EXIT_SUCCESS;
}
