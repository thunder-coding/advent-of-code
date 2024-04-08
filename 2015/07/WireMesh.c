#include "WireMesh.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void WireMesh_new(struct WireMesh *wireMesh) {
  wireMesh->size = 0;
  wireMesh->wires = NULL;
}

void WireMesh_free(struct WireMesh *wireMesh) {
  if (wireMesh->size != 0) {
    free(wireMesh->wires);
  }
  wireMesh->size = 0;
}

void *WireMesh_begin(struct WireMesh *wireMesh) { return wireMesh->wires; }

void *WireMesh_end(struct WireMesh *wireMesh) {
  return &wireMesh->wires[wireMesh->size];
}

void *WireMesh_find(struct WireMesh *wireMesh, char wire[2]) {
  size_t left = 0;
  size_t right = wireMesh->size;
  size_t mid;
  while (left < right) {
    mid = left + (right - left) / 2;
    if (*(uint16_t *)wireMesh->wires[mid].wire < *(uint16_t *)wire) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  if ((left == wireMesh->size) ||
      (*(uint16_t *)wireMesh->wires[left].wire != *(uint16_t *)wire)) {
    return WireMesh_end(wireMesh);
  }
  return &wireMesh->wires[left];
}

bool WireMesh_insert(struct WireMesh *wireMesh, char wire[2],
                     struct Wire *wireData) {
  size_t left = 0;
  size_t right = wireMesh->size;
  size_t mid;
  while (left < right) {
    mid = left + (right - left) / 2;
    if (*(uint16_t *)wireMesh->wires[mid].wire < *(uint16_t *)wire) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  if ((left == wireMesh->size) ||
      (*(uint16_t *)wireMesh->wires[left].wire != *(uint16_t *)wire)) {
    struct Wire *new_location =
        malloc(sizeof(struct Wire) * (wireMesh->size + 1));
    if (wireMesh->size != 0) {
      memcpy(new_location, wireMesh->wires,
             sizeof(struct Wire) * wireMesh->size);
    }
    if (left != wireMesh->size) {
      memmove(&new_location[left + 1], &new_location[left],
              sizeof(struct Wire) * (wireMesh->size - left));
    }
    new_location[left] = *wireData;
    if (wireMesh->size != 0) {
      free(wireMesh->wires);
    }
    wireMesh->size++;
    wireMesh->wires = new_location;
    return true;
  }
  return false;
}

bool calculate_wire_signal_from_WireMesh(char wireId[2],
                                         struct WireMesh *wireMesh,
                                         uint16_t *value) {
  struct Wire *wire = WireMesh_find(wireMesh, wireId);
  if (wire == WireMesh_end(wireMesh)) {
    fprintf(stderr, "'%2s' is not in the wireMesh", wireId);
    return false;
  }
  switch (wire->status) {
  case NotCalculated:
    wire->status = Calculating;
    break;
  case Calculating:
    fprintf(stderr, "Recursion detected while calculating for %s", wireId);
    return false;
    break;
  // Without caching it is super slow
  case Calculated:
    *value = wire->calculatedSignal;
    return true;
  }
  uint16_t a, b;
  switch (wire->gate) {
  case And:
  case Or:
  case Lshift:
  case Rshift: {
    switch (wire->b.type) {
    case SignalFromWire:
      if (!calculate_wire_signal_from_WireMesh(wire->b.raw.wireId, wireMesh,
                                               &b)) {
        return false;
      }
      break;
    case Raw:
      b = wire->b.raw.raw;
      break;
    }
  }
  case Not:
  case Copy: {
    switch (wire->a.type) {
    case SignalFromWire:
      if (!calculate_wire_signal_from_WireMesh(wire->a.raw.wireId, wireMesh,
                                               &a)) {
        return false;
      }
      break;
    case Raw:
      a = wire->a.raw.raw;
      break;
    }
  } break;
  default:
    fprintf(stderr, "Unexpected gate found");
    return false;
  }

  switch (wire->gate) {
  case And:
    *value = (a & b);
    break;
  case Or:
    *value = (a | b);
    break;
  case Lshift:
    *value = (a << b);
    break;
  case Rshift:
    *value = (a >> b);
    break;
  case Not:
    *value = ~a;
    break;
  case Copy:
    *value = a;
    break;
  // Should have been filtered by earlier switch
  default:
    break;
  }
  wire->status = Calculated;
  wire->calculatedSignal = *value;
  return true;
}
