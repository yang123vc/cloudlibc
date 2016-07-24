// Copyright (c) 2016 Nuxi, https://nuxi.nl/
//
// This file is distributed under a 2-clause BSD license.
// See the LICENSE file for details.

#include <stdint.h>

// SHA-512 hash computation state.
// http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf
typedef struct {
  uint64_t H[8];              // Intermediate hash results.
  uint64_t length[2];         // Total length in bytes processed.
  unsigned char buffer[128];  // Input buffer for partial blocks.
} SHA512_CTX;

#define SHA512_DIGEST_LENGTH 64

static void SHA512_Init(SHA512_CTX *ctx) {
  // Page 17: Initial hash value.
  ctx->H[0] = 0x6a09e667f3bcc908;
  ctx->H[1] = 0xbb67ae8584caa73b;
  ctx->H[2] = 0x3c6ef372fe94f82b;
  ctx->H[3] = 0xa54ff53a5f1d36f1;
  ctx->H[4] = 0x510e527fade682d1;
  ctx->H[5] = 0x9b05688c2b3e6c1f;
  ctx->H[6] = 0x1f83d9abfb41bd6b;
  ctx->H[7] = 0x5be0cd19137e2179;

  ctx->length[0] = 0;
  ctx->length[1] = 0;
}

// Page 20: Logical functions.
#define S(x, y) ((x) << (64 - (y)) | (x) >> (y))
#define R(x, y) ((x) >> (y))
#define Ch(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define Sigma0(x) (S(x, 28) ^ S(x, 34) ^ S(x, 39))
#define Sigma1(x) (S(x, 14) ^ S(x, 18) ^ S(x, 41))
#define sigma0(x) (S(x, 1) ^ S(x, 8) ^ R(x, 7))
#define sigma1(x) (S(x, 19) ^ S(x, 61) ^ R(x, 6))

static void SHA512_Transform(uint64_t *H, const unsigned char *block) {
  // Page 21: Constants table K.
  static const uint64_t K[] = {
      0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
      0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
      0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
      0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
      0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
      0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
      0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
      0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
      0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
      0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
      0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
      0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
      0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
      0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
      0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
      0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
      0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
      0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
      0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
      0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
      0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
      0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
      0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
      0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
      0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
      0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
      0x5fcb6fab3ad6faec, 0x6c44198c4a475817,
  };

  // Page 20: Expanded message block W.
  uint64_t W[80];
  for (size_t j = 0; j < 16; ++j)
    W[j] = (uint64_t)block[j * 8 + 0] << 56 | (uint64_t)block[j * 8 + 1] << 48 |
           (uint64_t)block[j * 8 + 2] << 40 | (uint64_t)block[j * 8 + 3] << 32 |
           (uint64_t)block[j * 8 + 4] << 24 | (uint64_t)block[j * 8 + 5] << 16 |
           (uint64_t)block[j * 8 + 6] << 8 | (uint64_t)block[j * 8 + 7] << 0;
  for (size_t j = 16; j < 80; ++j)
    W[j] = sigma1(W[j - 2]) + W[j - 7] + sigma0(W[j - 15]) + W[j - 16];

  // Page 19: Main loop.
  uint64_t a = H[0];
  uint64_t b = H[1];
  uint64_t c = H[2];
  uint64_t d = H[3];
  uint64_t e = H[4];
  uint64_t f = H[5];
  uint64_t g = H[6];
  uint64_t h = H[7];
  for (int j = 0; j < 80; ++j) {
    uint64_t T1 = h + Sigma1(e) + Ch(e, f, g) + K[j] + W[j];
    uint64_t T2 = Sigma0(a) + Maj(a, b, c);
    h = g;
    g = f;
    f = e;
    e = d + T1;
    d = c;
    c = b;
    b = a;
    a = T1 + T2;
  }
  H[0] += a;
  H[1] += b;
  H[2] += c;
  H[3] += d;
  H[4] += e;
  H[5] += f;
  H[6] += g;
  H[7] += h;
}

#undef S
#undef R
#undef Ch
#undef Maj
#undef Sigma0
#undef Sigma1
#undef sigma0
#undef sigma1

#define SHAX_CTX SHA512_CTX
#define SHAX_Final SHA512_Final
#define SHAX_Transform SHA512_Transform
#define SHAX_Update SHA512_Update
#include "crypt_hash_shaX.h"
#undef SHAX_CTX
#undef SHAX_Final
#undef SHAX_Transform
#undef SHAX_Update
