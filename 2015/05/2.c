#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Element {
  int prev;
  int curr;
  uint8_t pos;
};

struct Set {
  struct Element *elements;
  size_t size;
};

void Set_new(struct Set *set) {
  set->size = 0;
  set->elements = NULL;
}
void Set_free(struct Set *set) {
  if (set->size != 0)
    free(set->elements);
}

int Element_compare(const struct Element *a, const struct Element *b) {
  if (a->curr != b->curr) {
    return (a->curr < b->curr) ? -1 : 1;
  }
  if (a->prev == b->prev)
    return 0;
  return (a->prev < b->prev) ? -1 : 1;
}

const struct Element *Set_begin(struct Set *set) { return set->elements; }

const struct Element *Set_end(struct Set *set) {
  return &set->elements[set->size];
}

size_t Set_lower_bound(struct Set *set, const struct Element element) {
  size_t left = 0;
  size_t right = set->size;
  size_t mid;
  while (left < right) {
    mid = left + (right - left) / 2;
    if (Element_compare(&set->elements[mid], &element) < 0) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}
const struct Element *Set_find(struct Set *set, const struct Element element) {
  if (set->size == 0)
    return NULL;
  size_t left = 0;
  size_t right = set->size;
  size_t mid;
  while (left < right) {
    mid = left + (right - left) / 2;
    if (Element_compare(&set->elements[mid], &element) < 0) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  if (left == set->size || Element_compare(&set->elements[left], &element))
    return &set->elements[set->size];
  return &set->elements[left];
}

void Set_insert(struct Set *set, const struct Element element) {
  if (set->size == 0) {
    set->size++;
    set->elements = malloc(sizeof(struct Element));
    set->elements[0] = element;
    return;
  }
  size_t lb = Set_lower_bound(set, element);
  if ((lb == set->size) ||
      (Element_compare(&set->elements[lb], &element) != 0)) {
    set->size++;
    struct Element *new_location = malloc(sizeof(struct Element) * set->size);
    memcpy(new_location, set->elements,
           (set->size - 1) * sizeof(struct Element));
    free(set->elements);
    set->elements = new_location;
    if (lb < set->size - 1) {
      memmove(&set->elements[lb + 1], &set->elements[lb],
              (set->size - lb - 1) * sizeof(struct Element));
    }
    set->elements[lb] = element;
  }
}

enum String { Nice, Naughty };

enum String parse(FILE *file) {
  bool condition1 = false;
  bool condition2 = false;
  struct Element e = {.curr = EOF, .prev = EOF, .pos = 0};
  int prev2 = EOF;
  struct Set set;
  Set_new(&set);
  for (e.curr = fgetc(file); (e.curr != EOF) && (e.curr != '\n');
       prev2 = e.prev, e.prev = e.curr, e.curr = fgetc(file), e.pos++) {
    const struct Element *find = Set_find(&set, e);
    if (!condition1 && (find != Set_end(&set)) && (find->pos + 2 <= e.pos)) {
      condition1 = true;
    }
    if (!condition2 && prev2 == e.curr) {
      condition2 = true;
    }

    if (condition1 && condition2) {
      while (true) {
        switch (fgetc(file)) {
        case EOF:
        case '\n':
          Set_free(&set);
          return Nice;
        }
      }
    }
    Set_insert(&set, e);
  }
  Set_free(&set);
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
