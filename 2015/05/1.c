#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum String { Nice, Naughty };

enum String parse(FILE *file);

enum String parse(FILE *file) {
  int previous = EOF;
  int current = '\0';
  uint8_t vowelCount = 0;
  bool repeat = false;

  for (current = fgetc(file); current != EOF;
       previous = current, current = fgetc(file)) {
    if ((current == 'b' && previous == 'a') ||
        (current == 'd' && previous == 'c') ||
        (current == 'q' && previous == 'p') ||
        (current == 'y' && previous == 'x')) {
      while (true) {
        switch (fgetc(file)) {
        case EOF:
        case '\n':
          return Naughty;
        }
      }
    }

    if (current == previous) {
      repeat = true;
    }
    switch (current) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      vowelCount++;
      break;
    case '\n':
      goto end;
    }
  }
end:
  if (vowelCount >= 3 && repeat) {
    return Nice;
  }
  return Naughty;
}

int main() {
  FILE *input = fopen("./2015/05/input.txt", "r");
  if (!input) {
    fprintf(stderr, "Unable to open input file\n");
    return EXIT_FAILURE;
  }
  uint16_t niceCount = 0;
  while (!feof(input)) {
    if (parse(input) == Nice) {
      niceCount++;
    }
  }
  fclose(input);
  printf("%d", niceCount);
  return EXIT_SUCCESS;
}
