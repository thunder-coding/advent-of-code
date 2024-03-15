#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct House {
  int16_t x;
  int16_t y;
  unsigned int gift_count;
};

struct Houses {
  struct House *houses;
  size_t size;
};

struct Houses Houses_new() {
  struct Houses houses;
  houses.houses = NULL;
  houses.size = 0;
  return houses;
}

void Houses_free(struct Houses *houses) {
  free(houses->houses);
  houses->houses = NULL;
  houses->size = 0;
}

int Houses_compare(struct House a, struct House b) {
  /* return *(uint32_t *)&a - *(uint32_t *)&b; */
  if (a.x != b.x)
    return a.x - b.x;
  return a.y - b.y;
}

size_t Houses_lower_bound(struct Houses *houses, struct House house) {
  size_t left = 0;
  size_t right = houses->size;
  while (left < right) {
    size_t mid = left + (right - left) / 2;
    if (Houses_compare(houses->houses[mid], house) < 0) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}

void Houses_insert_if_not_exist(struct Houses *houses, struct House house) {
  if (houses->size == 0) {
    houses->houses = malloc(sizeof(struct House));
    houses->size = 1;
    houses->houses[0] = house;
    return;
  }
  size_t index = Houses_lower_bound(houses, house);
  if ((index == houses->size) || (houses->houses[index].x != house.x) ||
      (houses->houses[index].y != house.y)) {
    houses->size++;
    struct House *new_location = malloc(sizeof(struct House) * houses->size);
    memcpy(new_location, houses->houses,
           sizeof(struct House) * (houses->size - 1));
    free(houses->houses);
    houses->houses = new_location;
    if (index < houses->size - 1) {
      memmove(&houses->houses[index + 1], &houses->houses[index],
              (houses->size - index - 1) * sizeof(struct House));
    }
    houses->houses[index] = house;
  } else {
    houses->houses[index].gift_count++;
  }
}

int main() {
  FILE *input = fopen("./2015/03/input.txt", "r");
  if (!input) {
    fprintf(stderr, "Unable to open input file\n");
    return EXIT_FAILURE;
  }
  struct Houses houses = Houses_new();
  struct House house = {.x = 0, .y = 0, .gift_count = 1};
  Houses_insert_if_not_exist(&houses, house);
  int ch;
  while ((ch = fgetc(input)) != EOF) {
    switch (ch) {
    case '^':
      house.y++;
      break;
    case 'v':
      house.y--;
      break;
    case '>':
      house.x++;
      break;
    case '<':
      house.x--;
      break;
    default:
      fprintf(stderr, "Invalid character '%c' in input file\n", ch);
      return EXIT_FAILURE;
    }
    Houses_insert_if_not_exist(&houses, house);
  }
  printf("%zu", houses.size);
  Houses_free(&houses);
  fclose(input);
  return EXIT_SUCCESS;
}
