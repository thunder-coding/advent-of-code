#include "WireMesh.h"
#include "parser.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
  FILE *input = fopen("./2015/07/input.txt", "r");
  if (!input) {
    fprintf(stderr, "Unable to open input file\n");
    return EXIT_FAILURE;
  }
  struct Instruction instruction;
  struct WireMesh wireMesh;
  WireMesh_new(&wireMesh);
  struct Wire wire;
  wire.status = NotCalculated;
  for (int i = 0; true; i++) {
    instruction = parseInstruction(input);
    switch (instruction.gate) {
    case ParsingError:
      fprintf(stderr, "Error parsing input file on line %d", i);
      return EXIT_FAILURE;
    case Eof:
      goto after_parsing_instructions;
    case Not:
    case And:
    case Or:
    case Lshift:
    case Rshift:
    case Copy:
      wire.wire[0] = instruction.c.raw.wireId[0];
      wire.wire[1] = instruction.c.raw.wireId[1];
      wire.a = instruction.a;
      wire.b = instruction.b;
      wire.gate = instruction.gate;
      if (!WireMesh_insert(&wireMesh, instruction.c.raw.wireId, &wire)) {
        fprintf(stderr,
                "Error every wire can only have it's signal set by one source");
        return EXIT_FAILURE;
      }
      break;
    }
  }
after_parsing_instructions:
  fclose(input);
  uint16_t value;
  if (!calculate_wire_signal_from_WireMesh("a\0", &wireMesh, &value)) {
    return EXIT_FAILURE;
  }

  for (int i = 0; i != wireMesh.size; i++) {
    wireMesh.wires[i].status = NotCalculated;
  }

  struct Wire *bWire = WireMesh_find(&wireMesh, "b\0");

  if (bWire == WireMesh_end(&wireMesh)) {
    fprintf(stderr, "'b' wire not found in the mesh");
    return EXIT_FAILURE;
  }

  bWire->calculatedSignal = value;
  bWire->status = Calculated;
  if (!calculate_wire_signal_from_WireMesh("a\0", &wireMesh, &value)) {
    return EXIT_FAILURE;
  }
  printf("%" PRIu16, value);
  WireMesh_free(&wireMesh);
  return EXIT_SUCCESS;
}
