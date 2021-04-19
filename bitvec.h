#ifndef _BITVEC_H_
#define _BITVEC_H_

#include <stdint.h>

void bitvec_insert_bits(uint8_t *bitv, uint32_t nbits);
void bitvec_extract_bits(uint8_t *bitv, uint32_t nbits);

void bitvec_insert_byte(uint8_t byte);
uint8_t bitvec_extract_byte(void);

uint32_t bitvec_get_encoded_nbits(void);

void bitvec_init(uint8_t *encoded_data,
                 uint32_t encoded_nbits);

#endif
