#ifndef ADVENT_OF_CODE_2015_04_MD5_H
#define ADVENT_OF_CODE_2015_04_MD5_H
#include <stdint.h>

struct MD5_digest {
  uint64_t size;
  uint8_t digest[16];
};

void *MD5_new(const void *, uint64_t);
void MD5_free(void *);

static const uint8_t S[4][4] = {
    {7, 12, 17, 22},
    {5, 9, 14, 20},
    {4, 11, 16, 23},
    {6, 10, 15, 21},
};

#endif
