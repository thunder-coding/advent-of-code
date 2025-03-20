#[derive(Debug, Clone, Copy)]
pub struct MD5 {
  buffer: [u8; 64],
  A: u32,
  B: u32,
  C: u32,
  D: u32,
  length: u64,
}
static PADDING: [u8; 64] = [
  0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
];

static T: [u32; 64] = [
  0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501,
  0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE, 0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821,
  0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA, 0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8,
  0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED, 0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A,
  0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C, 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70,
  0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05, 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665,
  0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1,
  0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1, 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391,
];

impl MD5 {
  pub fn new() -> Self {
    return MD5 {
      buffer: [0; 64],
      A: 0x67452301,
      B: 0xEFCDAB89,
      C: 0x98BADCFE,
      D: 0x10325476,
      length: 0,
    };
  }

  pub fn consume(&mut self, data: Vec<u8>) {
    #[inline]
    fn bitwise_left_round_shift(X: u32, s: u32) -> u32 {
      return (X << (s % 32)) | (X >> (32 - (s % 32)));
    }

    for byte in data {
      self.buffer[(self.length % 64) as usize] = byte;
      self.length += 1;
      if self.length % 64 == 0 {
        let AA = self.A;
        let BB = self.B;
        let CC = self.C;
        let DD = self.D;
        let M = unsafe { std::mem::transmute::<[u8; 64], [u32; 16]>(self.buffer) };

        // Round 1.
        //
        // [abcd k s i] denotes a = b + ((a + F(b,c,d) + X[k] + T[i]) <<< s)
        //
        // [ABCD  0  7  1]  [DABC  1 12  2]  [CDAB  2 17  3]  [BCDA  3 22  4]
        // [ABCD  4  7  5]  [DABC  5 12  6]  [CDAB  6 17  7]  [BCDA  7 22  8]
        // [ABCD  8  7  9]  [DABC  9 12 10]  [CDAB 10 17 11]  [BCDA 11 22 12]
        // [ABCD 12  7 13]  [DABC 13 12 14]  [CDAB 14 17 15]  [BCDA 15 22 16]

        // F(X, Y, Z) = XY v not(X) Z
        #[inline]
        fn F(X: u32, Y: u32, Z: u32) -> u32 {
          return (X & Y) | ((!X) & Z);
        }
        macro_rules! R1 {
          ($A : expr, $B : expr, $C : expr, $D : expr, $k : expr, $s : expr,
               $i : expr) => {
            $A = u32::wrapping_add(
              $B,
              bitwise_left_round_shift(
                u32::wrapping_add(
                  u32::wrapping_add($A, F($B, $C, $D)),
                  u32::wrapping_add(M[$k], T[$i - 1]),
                ),
                $s,
              ),
            );
          };
        }
        R1!(self.A, self.B, self.C, self.D, 0, 7, 1);
        R1!(self.D, self.A, self.B, self.C, 1, 12, 2);
        R1!(self.C, self.D, self.A, self.B, 2, 17, 3);
        R1!(self.B, self.C, self.D, self.A, 3, 22, 4);
        R1!(self.A, self.B, self.C, self.D, 4, 7, 5);
        R1!(self.D, self.A, self.B, self.C, 5, 12, 6);
        R1!(self.C, self.D, self.A, self.B, 6, 17, 7);
        R1!(self.B, self.C, self.D, self.A, 7, 22, 8);
        R1!(self.A, self.B, self.C, self.D, 8, 7, 9);
        R1!(self.D, self.A, self.B, self.C, 9, 12, 10);
        R1!(self.C, self.D, self.A, self.B, 10, 17, 11);
        R1!(self.B, self.C, self.D, self.A, 11, 22, 12);
        R1!(self.A, self.B, self.C, self.D, 12, 7, 13);
        R1!(self.D, self.A, self.B, self.C, 13, 12, 14);
        R1!(self.C, self.D, self.A, self.B, 14, 17, 15);
        R1!(self.B, self.C, self.D, self.A, 15, 22, 16);
        // Round 2.
        //
        // [abcd k s i] denotes a = b + ((a + G(b,c,d) + X[k] + T[i]) <<< s)
        //
        // [ABCD  1  5 17]  [DABC  6  9 18]  [CDAB 11 14 19]  [BCDA  0 20 20]
        // [ABCD  5  5 21]  [DABC 10  9 22]  [CDAB 15 14 23]  [BCDA  4 20 24]
        // [ABCD  9  5 25]  [DABC 14  9 26]  [CDAB  3 14 27]  [BCDA  8 20 28]
        // [ABCD 13  5 29]  [DABC  2  9 30]  [CDAB  7 14 31]  [BCDA 12 20 32]

        // XZ v Y not(Z)

        #[inline]
        fn G(X: u32, Y: u32, Z: u32) -> u32 {
          return (X & Z) | (Y & (!Z));
        }
        macro_rules! R2 {
          ($A : expr, $B : expr, $C : expr, $D : expr, $k : expr, $s : expr,
               $i : expr) => {
            $A = u32::wrapping_add(
              $B,
              bitwise_left_round_shift(
                u32::wrapping_add(
                  u32::wrapping_add($A, G($B, $C, $D)),
                  u32::wrapping_add(M[$k], T[$i - 1]),
                ),
                $s,
              ),
            );
          };
        }
        R2!(self.A, self.B, self.C, self.D, 1, 5, 17);
        R2!(self.D, self.A, self.B, self.C, 6, 9, 18);
        R2!(self.C, self.D, self.A, self.B, 11, 14, 19);
        R2!(self.B, self.C, self.D, self.A, 0, 20, 20);
        R2!(self.A, self.B, self.C, self.D, 5, 5, 21);
        R2!(self.D, self.A, self.B, self.C, 10, 9, 22);
        R2!(self.C, self.D, self.A, self.B, 15, 14, 23);
        R2!(self.B, self.C, self.D, self.A, 4, 20, 24);
        R2!(self.A, self.B, self.C, self.D, 9, 5, 25);
        R2!(self.D, self.A, self.B, self.C, 14, 9, 26);
        R2!(self.C, self.D, self.A, self.B, 3, 14, 27);
        R2!(self.B, self.C, self.D, self.A, 8, 20, 28);
        R2!(self.A, self.B, self.C, self.D, 13, 5, 29);
        R2!(self.D, self.A, self.B, self.C, 2, 9, 30);
        R2!(self.C, self.D, self.A, self.B, 7, 14, 31);
        R2!(self.B, self.C, self.D, self.A, 12, 20, 32);

        // Round 3.
        // [abcd k s i] denotes a = b + ((a + H(b,c,d) + X[k] + T[i]) <<< s)
        //
        // [ABCD  5  4 33]  [DABC  8 11 34]  [CDAB 11 16 35]  [BCDA 14 23 36]
        // [ABCD  1  4 37]  [DABC  4 11 38]  [CDAB  7 16 39]  [BCDA 10 23 40]
        // [ABCD 13  4 41]  [DABC  0 11 42]  [CDAB  3 16 43]  [BCDA  6 23 44]
        // [ABCD  9  4 45]  [DABC 12 11 46]  [CDAB 15 16 47]  [BCDA  2 23 48]

        // X xor Y xor Z
        #[inline]
        pub fn H(X: u32, Y: u32, Z: u32) -> u32 {
          return (X ^ Y ^ Z);
        }
        macro_rules! R3 {
          ($A : expr, $B : expr, $C : expr, $D : expr, $k : expr, $s : expr,
               $i : expr) => {
            $A = u32::wrapping_add(
              $B,
              bitwise_left_round_shift(
                u32::wrapping_add(
                  u32::wrapping_add($A, H($B, $C, $D)),
                  u32::wrapping_add(M[$k], T[$i - 1]),
                ),
                $s,
              ),
            );
          };
        }
        R3!(self.A, self.B, self.C, self.D, 5, 4, 33);
        R3!(self.D, self.A, self.B, self.C, 8, 11, 34);
        R3!(self.C, self.D, self.A, self.B, 11, 16, 35);
        R3!(self.B, self.C, self.D, self.A, 14, 23, 36);
        R3!(self.A, self.B, self.C, self.D, 1, 4, 37);
        R3!(self.D, self.A, self.B, self.C, 4, 11, 38);
        R3!(self.C, self.D, self.A, self.B, 7, 16, 39);
        R3!(self.B, self.C, self.D, self.A, 10, 23, 40);
        R3!(self.A, self.B, self.C, self.D, 13, 4, 41);
        R3!(self.D, self.A, self.B, self.C, 0, 11, 42);
        R3!(self.C, self.D, self.A, self.B, 3, 16, 43);
        R3!(self.B, self.C, self.D, self.A, 6, 23, 44);
        R3!(self.A, self.B, self.C, self.D, 9, 4, 45);
        R3!(self.D, self.A, self.B, self.C, 12, 11, 46);
        R3!(self.C, self.D, self.A, self.B, 15, 16, 47);
        R3!(self.B, self.C, self.D, self.A, 2, 23, 48);

        // Round 4.
        // [abcd k s i] denotes a = b + ((a + I(b,c,d) + X[k] + T[i]) <<< s)
        //
        // [ABCD  0  6 49]  [DABC  7 10 50]  [CDAB 14 15 51]  [BCDA  5 21 52]
        // [ABCD 12  6 53]  [DABC  3 10 54]  [CDAB 10 15 55]  [BCDA  1 21 56]
        // [ABCD  8  6 57]  [DABC 15 10 58]  [CDAB  6 15 59]  [BCDA 13 21 60]
        // [ABCD  4  6 61]  [DABC 11 10 62]  [CDAB  2 15 63]  [BCDA  9 21 64]

        // Y xor (X v not(Z))
        #[inline]
        pub fn I(X: u32, Y: u32, Z: u32) -> u32 {
          return Y ^ (X | (!Z));
        }
        macro_rules! R4 {
          ($A : expr, $B : expr, $C : expr, $D : expr, $k : expr, $s : expr,
               $i : expr) => {
            $A = u32::wrapping_add(
              $B,
              bitwise_left_round_shift(
                u32::wrapping_add(
                  u32::wrapping_add($A, I($B, $C, $D)),
                  u32::wrapping_add(M[$k], T[$i - 1]),
                ),
                $s,
              ),
            );
          };
        }
        R4!(self.A, self.B, self.C, self.D, 0, 6, 49);
        R4!(self.D, self.A, self.B, self.C, 7, 10, 50);
        R4!(self.C, self.D, self.A, self.B, 14, 15, 51);
        R4!(self.B, self.C, self.D, self.A, 5, 21, 52);
        R4!(self.A, self.B, self.C, self.D, 12, 6, 53);
        R4!(self.D, self.A, self.B, self.C, 3, 10, 54);
        R4!(self.C, self.D, self.A, self.B, 10, 15, 55);
        R4!(self.B, self.C, self.D, self.A, 1, 21, 56);
        R4!(self.A, self.B, self.C, self.D, 8, 6, 57);
        R4!(self.D, self.A, self.B, self.C, 15, 10, 58);
        R4!(self.C, self.D, self.A, self.B, 6, 15, 59);
        R4!(self.B, self.C, self.D, self.A, 13, 21, 60);
        R4!(self.A, self.B, self.C, self.D, 4, 6, 61);
        R4!(self.D, self.A, self.B, self.C, 11, 10, 62);
        R4!(self.C, self.D, self.A, self.B, 2, 15, 63);
        R4!(self.B, self.C, self.D, self.A, 9, 21, 64);

        self.A = self.A.wrapping_add(AA);
        self.B = self.B.wrapping_add(BB);
        self.C = self.C.wrapping_add(CC);
        self.D = self.D.wrapping_add(DD);
      }
    }
  }

  pub fn compute(&mut self) -> [u8; 16] {
    let bit_length = self.length * 8;
    if (self.length % 64) < 56 {
      self.consume(PADDING[..((56 - (self.length % 64)) as usize)].to_vec());
    } else {
      self.consume(PADDING[..((120 - (self.length % 64)) as usize)].to_vec());
    }
    let mut length_bytes: Vec<u8> = Vec::new();
    length_bytes.resize(8, 0);

    for i in 0..8 {
      length_bytes[i] = ((bit_length >> (i * 8)) & 0xFF) as u8;
    }
    self.consume(length_bytes);
    let mut digest: [u8; 16] = [0; 16];
    for i in 0..4 {
      digest[i + 0] = ((self.A >> (i * 8)) & 0x000000FF) as u8;
      digest[i + 4] = ((self.B >> (i * 8)) & 0x000000FF) as u8;
      digest[i + 8] = ((self.C >> (i * 8)) & 0x000000FF) as u8;
      digest[i + 12] = ((self.D >> (i * 8)) & 0x000000FF) as u8;
    }
    return digest;
  }
}
