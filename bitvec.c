
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

// bit vector
static uint8_t *bitvec_data          = NULL;
static uint32_t bitvec_encoded_nbits = 0;

// TODO: optimize, this is unnecessary slow, use local registers
void bitvec_insert_bits(uint8_t *bv, uint32_t nbits)
{
  uint32_t bi;
  for (bi = 0; bi < nbits; bi++) {
    uint8_t newbit = (bv[bi >> 3] & (1 << (bi & 7))) ? 1 : 0;
    bitvec_data[bitvec_encoded_nbits >> 3] |= (newbit << (bitvec_encoded_nbits & 7));
    bitvec_encoded_nbits++;
    if ((bitvec_encoded_nbits & 7) == 0) {
      // clear next byte to be inserted into bitvector
      bitvec_data[bitvec_encoded_nbits >> 3] = 0;
    }
  }
}

// TODO: optimize, this is unnecessary slow, use local registers
void bitvec_extract_bits(uint8_t *bv, uint32_t nbits)
{
  int32_t bitvec_cur_pos = bitvec_encoded_nbits - nbits;
  uint8_t next_byte = 0;
  int32_t bv_wr_pos = 0;
  uint32_t bi;
  for (bi = 0; bi < nbits; bi++) {
    uint8_t curbit = (bitvec_data[bitvec_cur_pos >> 3] & (1 << (bitvec_cur_pos & 7))) ? 1 : 0;
    next_byte |= (curbit << (bi & 7));
    if ((bi & 7) == 7) {
      // store next extracted byte
      bv[bv_wr_pos++] = next_byte;
      next_byte = 0;
    }
    bitvec_cur_pos++;
    bitvec_encoded_nbits--;
  }
  if ((nbits & 7) > 0) {
    // store last extracted byte if uneven byte boundary
    bv[bv_wr_pos++] = next_byte;
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

uint32_t bitvec_get_encoded_nbits(void)
{
  return bitvec_encoded_nbits;
}

void bitvec_init(uint8_t *encoded_data,
                 uint32_t encoded_nbits)
{
  // Setup the encoded bit vector and length,
  // normally nbits is zero when staring encoding,
  // and if decoding nbits is full encoded length.
  bitvec_data          = encoded_data;
  bitvec_encoded_nbits = encoded_nbits;
}
