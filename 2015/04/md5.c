#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"
#include "md5_precompute.h"

static inline uint32_t rotatel(uint32_t x, uint32_t shift) {
  // x << shift first left shifts the thing by shift units
  //
  // x >> (32 - shift) right shifts the thing by (32 - shift) units
  //
  // Then bitwise OR gives the result which we want since the new bits after
  // shift are zero.
  return (x << shift) | (x >> (32 - shift));
}

static inline uint32_t F(uint32_t X, uint32_t Y, uint32_t Z) {
  return (X & Y) | ((~X) & Z);
}

static inline uint32_t G(uint32_t X, uint32_t Y, uint32_t Z) {
  return (X & Z) | (Y & (~Z));
}

static inline uint32_t H(uint32_t X, uint32_t Y, uint32_t Z) {
  return X ^ Y ^ Z;
}

static inline uint32_t I(uint32_t X, uint32_t Y, uint32_t Z) {
  return Y ^ (X | (~Z));
}

// https://www.rfc-editor.org/rfc/rfc1321
// although the RFC specifies a lot of these things in bits, we are doing it in
// bytes
void *MD5_new(const void *data, const uint64_t size) {
  // Padding is always supposed to be done. (RFC section 3.1 step 1)
  uint64_t padding_size;
  if (size % 64 < 56) {
    // We are missing a few bytes to get a 64n + 56 bytes form
    padding_size = 56 - (size % 64);
  } else {
    // We are having 64n + (>= 56) form, fill in the current chunk, and have
    // another chunk with exactly 56 bytes.
    padding_size = (64 - (size % 64)) + 56;
  }
  // this is supposed to be able to be broken into chunks of 512-bits or 64
  // bytes
  const uint64_t padded_size = size + padding_size + 8;
  // Thee padded message must be of form 64n + 56 bytes.
  // Last 8 bytes (64 bits) contains the original message size in uint64 format
  void *M = malloc(padded_size);
  memcpy(M, data, size);
  // Perform the actual padding.
  void *m = M + size;
  // The first bit is always supposed to be 1 and rest are to be filled with
  // zeroes
  *(uint8_t *)m = 0x80;
  m += sizeof(uint8_t);
  // We already written our first byte by the time we are reaching here.
  for (padding_size--; padding_size != 0; padding_size--) {
    // Actually pad it
    *(uint8_t *)m = 0x00;
    // Advance the pointer
    m += sizeof(uint8_t);
  }
  // Now append the original message size.
  // Bits are appended as 2 32-bit words, with low order word first
  // Also RFC wants size in bits, not bytes
  const uint64_t size_in_bits = size * 8;
  *(uint64_t *)m = size_in_bits;

  // the md5sum is a 128-bit output, or 16 bytes
  void *md5sum = malloc(16);
  // Break into 4 32-bit words as mentioned in the spec
  uint32_t *A = md5sum + sizeof(uint32_t) * 0;
  uint32_t *B = md5sum + sizeof(uint32_t) * 1;
  uint32_t *C = md5sum + sizeof(uint32_t) * 2;
  uint32_t *D = md5sum + sizeof(uint32_t) * 3;

  // Initialize the word buffers
  // RFC specifies the hexadecimal in an antique fashion by mentioning the
  // low-order bits first after breaking it into 8-bit words.
  //
  // A: 01234567
  // B: 89abcdef
  // C: fedcba98
  // D: 76543210
  *A = 0x67452301;
  *B = 0xefcdab89;
  *C = 0x98badcfe;
  *D = 0x10325476;

  // Represents the current chunk
  void *X = M;
  uint64_t k;
  // <<< is left round shift operator
  //
  // Some other notes, original RFC does not give the relation between i and k,
  // but can be easily guessed looking at the pattern in the values.
  // Morever,Wikipedia also mentions the relation in it's MD5 article under the
  // pseudocode section (https://en.wikipedia.org/wiki/MD5#Pseudocode)
  for (uint64_t num_chunks = padded_size / 64, current_chunk = 0;
       current_chunk < num_chunks; current_chunk++) {
    uint32_t AA = *A;
    uint32_t BB = *B;
    uint32_t CC = *C;
    uint32_t DD = *D;
    for (int i = 0; i < 64; i++) {
      // Round 1
      // [abcd k s i] denotes:
      // a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s),
      // where,
      //        s = S[i / 16][i % 4]
      //        k = i
      if (i < 16) {
        k = i;
        *A = *B + rotatel(((*A + F(*B, *C, *D)) + ((uint32_t *)X)[k] + T[i]),
                          S[i / 16][i % 4]);
        // print k s i
      }
      // Round 2
      // [abcd k s i] denotes:
      // a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s),
      // where,
      //        s = S[i / 16][i % 4]
      //        k = ((5 * i) + 1) % 16
      else if (i < 32) {
        k = ((5 * i) + 1) % 16;
        *A = *B + rotatel(((*A + G(*B, *C, *D)) + ((uint32_t *)X)[k] + T[i]),
                          S[i / 16][i % 4]);
      }
      // Round 3
      // [abcd k s i] denotes:
      // a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s),
      // where,
      //        s = S[i / 16][i % 4]
      //        k = ((3 * i) + 5) % 16
      else if (i < 48) {
        k = ((3 * i) + 5) % 16;
        *A = *B + rotatel(((*A + H(*B, *C, *D)) + ((uint32_t *)X)[k] + T[i]),
                          S[i / 16][i % 4]);
      }
      // Round 4
      // [abcd k s i] denotes:
      // a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s),
      // where,
      //        s = S[i / 16][i % 4]
      //        k = (7 * i) % 16
      else /* if ( i < 64) */ {
        k = (7 * i) % 16;
        *A = *B + rotatel(((*A + I(*B, *C, *D)) + ((uint32_t *)X)[k] + T[i]),
                          S[i / 16][i % 4]);
      }
      // Rotate the variables;
      uint32_t *temp = A;
      A = D;
      D = C;
      C = B;
      B = temp;
    }
    *A += AA;
    *B += BB;
    *C += CC;
    *D += DD;
    X += 64;
  }
  free(M);
  return md5sum;
}

void MD5_free(void *data) { free(data); }
