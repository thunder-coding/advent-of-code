#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>

int getArea(std::ifstream &input) {
  std::array<int, 3> sides = {0, 0, 0};
  int index = 0;
  int ch = input.get();
  // handle UNIX style end of file, i.e. \n at the end
  if (ch == EOF) {
    return 0;
  }
  while (true) {
    switch (ch) {
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
      sides[index] *= 10;
      sides[index] += (ch - '0');
      break;
    case 'x':
      if (++index == 3) {
        std::cerr << "A cuboid has only 3 sides" << std::endl;
        return -1;
      }
      break;
    case '\n':
    case EOF:
      if (index != 2) {
        std::cerr << "A cuboid has exactly 3 sides not " << index + 1
                  << std::endl;
        return -1;
      }
      goto end;
      break;
    default:
      std::cerr << "Unexpected character in input file: '" << char(ch) << "'";
      return -1;
    }
    ch = input.get();
  }
end:
  std::sort(sides.begin(), sides.end());
  return 3 * sides[0] * sides[1] + 2 * sides[2] * (sides[0] + sides[1]);
}

int main() {
  auto input = std::ifstream("./2015/02/input.txt");
  if (!input.good()) {
    std::cerr << "Error opening file './2015/01/input.txt'" << std::endl;
    return EXIT_FAILURE;
  }
  int area = 0;
  int a;
  while ((a = getArea(input)) > 0)
    area += a;

  if (a == -1)
    return EXIT_FAILURE;
  std::cout << area;
  return EXIT_SUCCESS;
}
