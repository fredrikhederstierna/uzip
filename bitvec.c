
/* Simple bitvector
 * Fredrik Hederstierna 2021 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

#include <bitvec.h>

#define BITVEC_SIZE_BITS  (256)
#define BITVEC_SIZE_BYTES (BITVEC_SIZE_BITS / 8)

static uint8_t  bitvec[BITVEC_SIZE_BYTES+1];
static uint32_t bitvec_end_pos = 0;

void bitvec_insert_bits(uint8_t *bitv, uint32_t nbits)
{
  uint32_t bi;
  for (bi = 0; bi < nbits; bi++) {
    uint8_t newbit = (bitv[bi >> 3] & (1 << (bi & 7))) ? 1 : 0;
    bitvec[bitvec_end_pos >> 3] |= (newbit << (bitvec_end_pos & 7));
    bitvec_end_pos++;
    if ((bitvec_end_pos & 7) == 0) {
      bitvec[bitvec_end_pos >> 3] = 0;
    }
  }
}

void bitvec_extract_bits(uint8_t *bitv, uint32_t nbits)
{
  int32_t bitvec_cur_pos = bitvec_end_pos - nbits;
  uint8_t next_byte = 0;
  int32_t bitv_pos = 0;
  uint32_t bi;
  for (bi = 0; bi < nbits; bi++) {
    uint8_t curbit = (bitvec[bitvec_cur_pos >> 3] & (1 << (bitvec_cur_pos & 7))) ? 1 : 0;
    next_byte |= (curbit << (bi & 7));
    if ((bi & 7) == 7) {
      // store next byte
      bitv[bitv_pos++] = next_byte;
      next_byte = 0;
    }
    bitvec_cur_pos++;
    bitvec_end_pos--;
  }
  // store last byte
  if ((nbits & 7) > 0) {
    bitv[bitv_pos++] = next_byte;
  }
}

void bitvec_insert_byte(uint8_t byte)
{
  bitvec_insert_bits(&byte, 8);
}

uint8_t bitvec_extract_byte(void)
{
  uint8_t byte;
  bitvec_extract_bits(&byte, 8);
  return byte;
}

uint32_t bitvec_get_nbr_bits(void)
{
  return bitvec_end_pos;
}

void bitvec_init(void)
{
  bitvec_end_pos = 0;
}
