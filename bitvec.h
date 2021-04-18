#ifndef _BITVEC_H_
#define _BITVEC_H_

#include <stdint.h>

void bitvec_insert_bits(uint8_t *bitv, uint32_t nbits);
void bitvec_extract_bits(uint8_t *bitv, uint32_t nbits);

void bitvec_insert_byte(uint8_t byte);
uint8_t bitvec_extract_byte(void);

uint32_t bitvec_get_nbr_bits(void);

void bitvec_init(void);

#endif
