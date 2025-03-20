#include "md5.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <iostream>
#include <vector>

// A sequence of bits can be interpreted in a
// natural manner as a sequence of bytes, where each consecutive group
// of eight bits is interpreted as a byte with the high-order (most
// significant) bit of each byte listed first. Similarly, a sequence of
// bytes can be interpreted as a sequence of 32-bit words, where each
// consecutive group of four bytes is interpreted as a word with the
// low-order (least significant) byte given first.

inline auto bitwise_left_round_shift(const uint32_t& X, const uint32_t& s)
    -> uint32_t {
  return (X << (s % 32)) | (X >> (32 - (s % 32)));
}

// F(X, Y, Z) = XY v not(X) Z
inline auto F(const uint32_t& X, const uint32_t& Y, const uint32_t& Z)
    -> uint32_t {
  return (X & Y) | ((~X) & Z);
}

// XZ v Y not(Z)
inline auto G(const uint32_t& X, const uint32_t& Y, const uint32_t& Z)
    -> uint32_t {
  return (X & Z) | (Y & (~Z));
}

// X xor Y xor Z
inline auto H(const uint32_t& X, const uint32_t& Y, const uint32_t& Z)
    -> uint32_t {
  return X ^ Y ^ Z;
}

// Y xor (X v not(Z))
inline auto I(const uint32_t& X, const uint32_t& Y, const uint32_t& Z)
    -> uint32_t {
  return Y ^ (X | (~Z));
}

Helpers::MD5::MD5() {
  length = 0;
  // Step 3. Initialize the MD buffer
  A = 0x67452301;
  B = 0xefcdab89;
  C = 0x98badcfe;
  D = 0x10325476;
}

void Helpers::MD5::consume(const std::vector<uint8_t>& data) {
  // Step 4. Process message in 16-word blocks
  // Little and big endian doesn't matter here as bitwise shift operators output
  // same result irrespective of endianness So, we do not do any conversion here
  // and save computational time
  for (const auto& byte : data) {
    buffer[length % 64] = byte;
    length++;
    if (length % 64 == 0) {
      // We just filled our buffer. Now it's time to do some computation and
      // empty it
      uint32_t AA = A;
      uint32_t BB = B;
      uint32_t CC = C;
      uint32_t DD = D;

// Round 1.
//
// [abcd k s i] denotes a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s)
//
// [ABCD  0  7  1]  [DABC  1 12  2]  [CDAB  2 17  3]  [BCDA  3 22  4]
// [ABCD  4  7  5]  [DABC  5 12  6]  [CDAB  6 17  7]  [BCDA  7 22  8]
// [ABCD  8  7  9]  [DABC  9 12 10]  [CDAB 10 17 11]  [BCDA 11 22 12]
// [ABCD 12  7 13]  [DABC 13 12 14]  [CDAB 14 17 15]  [BCDA 15 22 16]
#define R1(A, B, C, D, k, s, i)     \
  A = B + bitwise_left_round_shift( \
              (A + F(B, C, D) + ((uint32_t*)buffer.data())[k] + T[i - 1]), s);
      // clang-format off
      R1(A, B, C, D,  0,  7,  1);
      R1(D, A, B, C,  1, 12,  2);
      R1(C, D, A, B,  2, 17,  3);
      R1(B, C, D, A,  3, 22,  4);
      R1(A, B, C, D,  4,  7,  5);
      R1(D, A, B, C,  5, 12,  6);
      R1(C, D, A, B,  6, 17,  7);
      R1(B, C, D, A,  7, 22,  8);
      R1(A, B, C, D,  8,  7,  9);
      R1(D, A, B, C,  9, 12, 10);
      R1(C, D, A, B, 10, 17, 11);
      R1(B, C, D, A, 11, 22, 12);
      R1(A, B, C, D, 12,  7, 13);
      R1(D, A, B, C, 13, 12, 14);
      R1(C, D, A, B, 14, 17, 15);
      R1(B, C, D, A, 15, 22, 16);
      // clang-format on

// Round 2.
//
// [abcd k s i] denotes a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s)
//
// [ABCD  1  5 17]  [DABC  6  9 18]  [CDAB 11 14 19]  [BCDA  0 20 20]
// [ABCD  5  5 21]  [DABC 10  9 22]  [CDAB 15 14 23]  [BCDA  4 20 24]
// [ABCD  9  5 25]  [DABC 14  9 26]  [CDAB  3 14 27]  [BCDA  8 20 28]
// [ABCD 13  5 29]  [DABC  2  9 30]  [CDAB  7 14 31]  [BCDA 12 20 32]
#define R2(A, B, C, D, k, s, i)     \
  A = B + bitwise_left_round_shift( \
              (A + G(B, C, D) + ((uint32_t*)buffer.data())[k] + T[i - 1]), s);
      // clang-format off
      R2(A, B, C, D,  1,  5, 17);
      R2(D, A, B, C,  6,  9, 18);
      R2(C, D, A, B, 11, 14, 19);
      R2(B, C, D, A,  0, 20, 20);
      R2(A, B, C, D,  5,  5, 21);
      R2(D, A, B, C, 10,  9, 22);
      R2(C, D, A, B, 15, 14, 23);
      R2(B, C, D, A,  4, 20, 24);
      R2(A, B, C, D,  9,  5, 25);
      R2(D, A, B, C, 14,  9, 26);
      R2(C, D, A, B,  3, 14, 27);
      R2(B, C, D, A,  8, 20, 28);
      R2(A, B, C, D, 13,  5, 29);
      R2(D, A, B, C,  2,  9, 30);
      R2(C, D, A, B,  7, 14, 31);
      R2(B, C, D, A, 12, 20, 32);
      // clang-format on

// Round 3.
// [abcd k s i] denotes a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s)
//
// [ABCD  5  4 33]  [DABC  8 11 34]  [CDAB 11 16 35]  [BCDA 14 23 36]
// [ABCD  1  4 37]  [DABC  4 11 38]  [CDAB  7 16 39]  [BCDA 10 23 40]
// [ABCD 13  4 41]  [DABC  0 11 42]  [CDAB  3 16 43]  [BCDA  6 23 44]
// [ABCD  9  4 45]  [DABC 12 11 46]  [CDAB 15 16 47]  [BCDA  2 23 48]
#define R3(A, B, C, D, k, s, i)     \
  A = B + bitwise_left_round_shift( \
              (A + H(B, C, D) + ((uint32_t*)buffer.data())[k] + T[i - 1]), s);
      // clang-format off
      R3(A, B, C, D,  5,  4, 33);
      R3(D, A, B, C,  8, 11, 34);
      R3(C, D, A, B, 11, 16, 35);
      R3(B, C, D, A, 14, 23, 36);
      R3(A, B, C, D,  1,  4, 37);
      R3(D, A, B, C,  4, 11, 38);
      R3(C, D, A, B,  7, 16, 39);
      R3(B, C, D, A, 10, 23, 40);
      R3(A, B, C, D, 13,  4, 41);
      R3(D, A, B, C,  0, 11, 42);
      R3(C, D, A, B,  3, 16, 43);
      R3(B, C, D, A,  6, 23, 44);
      R3(A, B, C, D,  9,  4, 45);
      R3(D, A, B, C, 12, 11, 46);
      R3(C, D, A, B, 15, 16, 47);
      R3(B, C, D, A,  2, 23, 48);
// clang-format on

// Round 4.
// [abcd k s i] denotes a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s)
//
// [ABCD  0  6 49]  [DABC  7 10 50]  [CDAB 14 15 51]  [BCDA  5 21 52]
// [ABCD 12  6 53]  [DABC  3 10 54]  [CDAB 10 15 55]  [BCDA  1 21 56]
// [ABCD  8  6 57]  [DABC 15 10 58]  [CDAB  6 15 59]  [BCDA 13 21 60]
// [ABCD  4  6 61]  [DABC 11 10 62]  [CDAB  2 15 63]  [BCDA  9 21 64]
#define R4(A, B, C, D, k, s, i)     \
  A = B + bitwise_left_round_shift( \
              (A + I(B, C, D) + ((uint32_t*)buffer.data())[k] + T[i - 1]), s);
      // clang-format off
      R4(A, B, C, D,  0,  6, 49);
      R4(D, A, B, C,  7, 10, 50);
      R4(C, D, A, B, 14, 15, 51);
      R4(B, C, D, A,  5, 21, 52);
      R4(A, B, C, D, 12,  6, 53);
      R4(D, A, B, C,  3, 10, 54);
      R4(C, D, A, B, 10, 15, 55);
      R4(B, C, D, A,  1, 21, 56);
      R4(A, B, C, D,  8,  6, 57);
      R4(D, A, B, C, 15, 10, 58);
      R4(C, D, A, B,  6, 15, 59);
      R4(B, C, D, A, 13, 21, 60);
      R4(A, B, C, D,  4,  6, 61);
      R4(D, A, B, C, 11, 10, 62);
      R4(C, D, A, B,  2, 15, 63);
      R4(B, C, D, A,  9, 21, 64);
      // clang-format on

      A = A + AA;
      B = B + BB;
      C = C + CC;
      D = D + DD;
    }
  }
}

auto Helpers::MD5::compute() -> std::array<uint8_t, 16> {
  // Calculate bit length before as we are modifying length in consume() call
  uint64_t bit_length = length * 8;

  // Step 1. Padding
  if ((length % 64) < 56) {
    this->consume(std::vector<uint8_t>(padding.begin(),
                                       padding.begin() + 56 - (length % 64)));
  } else {
    this->consume(std::vector<uint8_t>(padding.begin(),
                                       padding.begin() + 120 - (length % 64)));
  }
  // Step 2. Append Length
  std::vector<uint8_t> length_bits = {};
  length_bits.resize(8);

  for (int i = 0; i < 8; i++) {
    length_bits[i] = uint8_t((bit_length >> (i * 8)) & 0xFF);
  }
  this->consume(length_bits);
  assert(length % 64 == 0);
  std::array<uint8_t, 16> digest;
  for (int i = 0; i < 4; i++) {
    // clang-format off
    digest[i + 0]  = uint8_t((A >> (i * 8)) & 0x000000FF);
    digest[i + 4]  = uint8_t((B >> (i * 8)) & 0x000000FF);
    digest[i + 8]  = uint8_t((C >> (i * 8)) & 0x000000FF);
    digest[i + 12] = uint8_t((D >> (i * 8)) & 0x000000FF);
    // clang-format on
  }
  return digest;
}