#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>

int main() {
  auto input = std::ifstream("./2015/01/input.txt");
  if (!input.good()) {
    std::cerr << "Error opening file './2015/01/input.txt'" << std::endl;
    return EXIT_FAILURE;
  }
  int floor = 0;
  while (true) {
    int ch = input.get();
    if (input.eof())
      break;
    switch (ch) {
    case '(':
      floor++;
      break;
    case ')':
      floor--;
      break;
    default:
      std::cerr << "Warning unknown character '" << ch << "'" << std::endl;
      break;
    }
  }
  std::cout << floor << std::endl;
  return EXIT_SUCCESS;
}
