#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int get_surface_area(FILE *input) {
  int sides[3] = {0, 0, 0};
  int faces[3];
  int index = 0;
  int smallest_face;
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
  faces[0] = sides[0] * sides[1];
  faces[1] = sides[1] * sides[2];
  faces[2] = sides[2] * sides[0];
  smallest_face = faces[0];
  if (smallest_face > faces[1])
    smallest_face = faces[1];
  if (smallest_face > faces[2])
    smallest_face = faces[2];
  return (2 * (faces[0] + faces[1] + faces[2])) + smallest_face;
}

int main() {
  FILE *input = fopen("./2015/02/input.txt", "r");
  if (!input) {
    fprintf(stderr, "Unable to open input file\n");
    return EXIT_FAILURE;
  }

  int area;
  int total_area = 0;
  while ((area = get_surface_area(input)) != 0) {
    if (area == -1)
      return EXIT_FAILURE;
    total_area += area;
  }

  fclose(input);
  printf("Total area of wrapping paper will be %d square feet", total_area);
  return EXIT_SUCCESS;
}
