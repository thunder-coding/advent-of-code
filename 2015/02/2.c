#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int get_ribbon_length(FILE *input) {
  int sides[3] = {0, 0, 0};
  int smallest_perimeter;
  int index = 0;
  int ch;
  if ((ch = fgetc(input)) == EOF)
    return 0;
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
        fprintf(stderr, "A cubiod has only 3 sides\n");
        return -1;
      }
      break;
    case '\n':
      if (index != 2) {
        fprintf(stderr, "A cubiod has 3 sides not %d", index + 1);
        return -1;
      }
    case EOF:
      goto end;
      break;
    default:
      fprintf(stderr, "Unknown character encountered in file\n");
      return -1;
    }
    ch = fgetc(input);
  }
end:
  if (sides[0] >= sides[1]) {
    if (sides[0] >= sides[2]) {
      smallest_perimeter = 2 * (sides[1] + sides[2]);
    } else {
      smallest_perimeter = 2 * (sides[0] + sides[1]);
    }
  } else {
    if (sides[1] >= sides[2]) {
      smallest_perimeter = 2 * (sides[0] + sides[2]);
    } else {
      smallest_perimeter = 2 * (sides[0] + sides[1]);
    }
  }
  return smallest_perimeter + sides[0] * sides[1] * sides[2];
}

int main() {
  FILE *input = fopen("./2015/02/input.txt", "r");
  if (!input) {
    fprintf(stderr, "Unable to open input file\n");
    return EXIT_FAILURE;
  }

  int ribbon_length = 0;
  int l;
  while ((l = get_ribbon_length(input)) != 0) {
    if (l == -1)
      return EXIT_FAILURE;
    ribbon_length += l;
  }
  printf("Length of ribbon required is %d feet", ribbon_length);
  return EXIT_SUCCESS;
}
