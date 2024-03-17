#include "md5.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main() {
  FILE *input = fopen("./2015/04/input.txt", "r");
  if (!input) {
    fprintf(stderr, "Unable to open input file\n");
    return EXIT_FAILURE;
  }
  int ch;
  char *secret;
  size_t secretSize = 0;
  while ((ch = fgetc(input)) != EOF) {
    secretSize++;
    char *newSecret = malloc(secretSize);
    if (secretSize > 0) {
      memcpy(newSecret, secret, secretSize - 1);
      free(secret);
    }
    newSecret[secretSize - 1] = ch;
    secret = newSecret;
  }
  fclose(input);

  uint64_t answer = 1;
  // INT64_MAX is 20 characters +1 for the terminating '\0'
  char *string = malloc(secretSize + 21);
  memcpy(string, secret, secretSize);
  free(secret);
  while (answer != UINT64_MAX) {
    size_t intsize = sprintf(string + secretSize, "%zu", answer);
    void *hash = MD5_new(string, secretSize + intsize);
    if ((((uint8_t *)hash)[0] == 0) && (((uint8_t *)hash)[1] == 0) &&
        (((uint8_t *)hash)[2] < 0x10)) {
      printf("%" PRIu64, answer);
      return EXIT_SUCCESS;
    }
    MD5_free(hash);
    answer++;
  }
  fprintf(stderr, "No value of integer till UINT64 gives the desired result");
  return EXIT_FAILURE;
}
