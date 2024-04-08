#ifndef ADVENT_OF_CODE_2015_07_WIREMESH_H
#define ADVENT_OF_CODE_2015_07_WIREMESH_H
#include "parser.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
enum WireStatus { NotCalculated, Calculating, Calculated };

struct Wire {
  char wire[2];
  enum WireStatus status;
  uint16_t calculatedSignal;
  enum Gate gate;
  struct Signal a, b;
};

struct WireMesh {
  struct Wire *wires;
  size_t size;
};

void WireMesh_new(struct WireMesh *wireMesh);
void WireMesh_free(struct WireMesh *wireMesh);
void *WireMesh_begin(struct WireMesh *wireMesh);
void *WireMesh_end(struct WireMesh *wireMesh);
void *WireMesh_find(struct WireMesh *wireMesh, char wire[2]);
bool WireMesh_insert(struct WireMesh *wireMesh, char wire[2],
                     struct Wire *wireData);

bool calculate_wire_signal_from_WireMesh(char wireId[2],
                                         struct WireMesh *wireMesh,
                                         uint16_t *value);
#endif
