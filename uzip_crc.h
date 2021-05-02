#ifndef _UZIP_CRC_H_
#define _UZIP_CRC_H_

#include <stdint.h>

// Compute CRC32 without lookup tables.
// (Starting condition for crc_prev is 0)
uint32_t uzip_crc32_calc(const void* data, uint32_t len, uint32_t prev_crc);

#endif
