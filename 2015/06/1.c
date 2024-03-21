#include "input_parser.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Lightgrid {
  bool lights[1000][1000];
};
void Lightgrid_new(struct Lightgrid *lightgrid);
void Lightgrid_toggle(struct Lightgrid *lightgrid, const int startx,
                      const int starty, const int endx, const int endy);
void Lightgrid_turnon(struct Lightgrid *lightgrid, const int startx,
                      const int starty, const int endx, const int endy);
void Lightgrid_turnoff(struct Lightgrid *lightgrid, const int startx,
                       const int starty, const int endx, const int endy);
uint32_t Lightgrid_counton(struct Lightgrid *lightgrid);

void Lightgrid_new(struct Lightgrid *lightgrid) {
  for (int x = 0; x < 1000; x++) {
    for (int y = 0; y < 1000; y++) {
      lightgrid->lights[x][y] = false;
    }
  }
}

void Lightgrid_toggle(struct Lightgrid *lightgrid, const int startx,
                      const int starty, const int endx, const int endy) {
  const int stepx = (startx < endx) ? +1 : -1;
  const int stepy = (starty < endy) ? +1 : -1;
  for (int x = startx; x != (endx + stepx); x += stepx) {
    for (int y = starty; y != (endy + stepy); y += stepy) {
      lightgrid->lights[x][y] = !lightgrid->lights[x][y];
    }
  }
}

void Lightgrid_turnon(struct Lightgrid *lightgrid, const int startx,
                      const int starty, const int endx, const int endy) {
  const int stepx = (startx < endx) ? +1 : -1;
  const int stepy = (starty < endy) ? +1 : -1;
  for (int x = startx; x != (endx + stepx); x += stepx) {
    for (int y = starty; y != (endy + stepy); y += stepy) {
      lightgrid->lights[x][y] = true;
    }
  }
}

void Lightgrid_turnoff(struct Lightgrid *lightgrid, const int startx,
                       const int starty, const int endx, const int endy) {
  const int stepx = (startx < endx) ? +1 : -1;
  const int stepy = (starty < endy) ? +1 : -1;
  for (int x = startx; x != (endx + stepx); x += stepx) {
    for (int y = starty; y != (endy + stepy); y += stepy) {
      lightgrid->lights[x][y] = false;
    }
  }
}

uint32_t Lightgrid_counton(struct Lightgrid *lightgrid) {
  uint32_t count = 0;
  for (int x = 0; x < 1000; x++) {
    for (int y = 0; y < 1000; y++) {
      if (lightgrid->lights[x][y]) {
        count++;
      }
    }
  }
  return count;
}
int main() {
  FILE *input = fopen("./2015/06/input.txt", "r");
  if (!input) {
    fprintf(stderr, "Unable to open input file\n");
    return EXIT_FAILURE;
  }
  struct Instruction instruction;
  struct Lightgrid lightgrid;
  Lightgrid_new(&lightgrid);
  while (true) {
    Parse_instruction(input, &instruction);
    switch (instruction.action) {
    case Error:
      fprintf(stderr, "Error parsing input file\n");
      return EXIT_FAILURE;
    case Eof:
      goto end;
    case TurnOn:
      Lightgrid_turnon(&lightgrid, instruction.startx, instruction.starty,
                       instruction.endx, instruction.endy);
      break;
    case TurnOff:
      Lightgrid_turnoff(&lightgrid, instruction.startx, instruction.starty,
                        instruction.endx, instruction.endy);
      break;
    case Toggle:
      Lightgrid_toggle(&lightgrid, instruction.startx, instruction.starty,
                       instruction.endx, instruction.endy);
      break;
    }
  }
end:
  fclose(input);
  printf("%" PRIu32 "\n", Lightgrid_counton(&lightgrid));
  return EXIT_SUCCESS;
}
