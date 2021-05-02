#include <stdint.h>
#include <uzip_crc.h>

// CRC32 polynomial used by zlib
#define POLY_CRC32 0xEDB88320

// Compute CRC32 without lookup tables.
// Idea from: "https://create.stephan-brumme.com/crc32/"
// (Algorithm originally found in "Hacker's Delight" by Henry S. Warren)
uint32_t uzip_crc32_calc(const void* data, uint32_t len, uint32_t prev_crc)
{
  // use signed integer, right shifting preserves the sign bit
  int32_t crc = ~prev_crc;
  const uint8_t* cur = (const uint8_t*)data;

  while (len--) {
    crc = crc ^ *cur++;

    uint32_t c =
      (((crc << 31) >> 31) & ((POLY_CRC32 >> 7)  ^ (POLY_CRC32 >> 1))) ^
      (((crc << 30) >> 31) & ((POLY_CRC32 >> 6)  ^  POLY_CRC32)) ^
      (((crc << 29) >> 31) &  (POLY_CRC32 >> 5)) ^
      (((crc << 28) >> 31) &  (POLY_CRC32 >> 4)) ^
      (((crc << 27) >> 31) &  (POLY_CRC32 >> 3)) ^
      (((crc << 26) >> 31) &  (POLY_CRC32 >> 2)) ^
      (((crc << 25) >> 31) &  (POLY_CRC32 >> 1)) ^
      (((crc << 24) >> 31) &  (POLY_CRC32 >> 0));

    // use unsigned integer, before right shift without sign bit preserved
    crc = ((uint32_t)crc >> 8) ^ c;
  }

  // negate, same as (crc ^ 0xFFFFFFFF)
  return ~crc;
}
