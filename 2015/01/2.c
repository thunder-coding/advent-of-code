#include <stdio.h>
#include <stdlib.h>

#define basement_floor -1

int main(void) {
  FILE *input = fopen("./2015/01/input.txt", "r");
  if (!input) {
    fprintf(stderr, "Unable to open input file\n");
    return EXIT_FAILURE;
  }
  int floor = 0;
  int c;
  unsigned int iteration = 0;
  while ((c = fgetc(input)) != EOF) {
    iteration++;
    switch (c) {
    case '(':
      floor++;
      break;
    case ')':
      floor--;
      break;
    default:
      fprintf(stderr, "Warning invalid character: '%c'\n", c);
      break;
    }
    if (floor == basement_floor) {
      printf("%d", iteration);
      return EXIT_SUCCESS;
    }
  }
  fclose(input);
  fprintf(stderr, "Santa never reached the basement");
  return EXIT_FAILURE;
}
