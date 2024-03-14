#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *input = fopen("./2015/01/input.txt", "r");
  if (!input) {
    fprintf(stderr, "Unable to open input file\n");
    return EXIT_FAILURE;
  }
  int floor = 0;
  int c;
  while ((c = fgetc(input)) != EOF) {
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
  }
  fclose(input);
  printf("Santa should be at floor %d\n", floor);
  return EXIT_SUCCESS;
}
