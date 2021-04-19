/* Simple Lempel-Ziv codec
   Fredrik Hederstierna 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

#include <bitvec.h>

#define UZIP_CODEC_BUF_SIZE (256)
static uint8_t encoder_data[UZIP_CODEC_BUF_SIZE] = { 0 };
static uint8_t decoder_data[UZIP_CODEC_BUF_SIZE] = { 0 };

//--------------------------------
int main(int argc, char **argv)
{
  int ret = EXIT_SUCCESS;

#if 0
  if (argc != 2) {
    printf("No filename argument found, argc = %d.\n", argc);
    goto exit_main;
  }
  char *filename = argv[1];
#endif

  bitvec_init(encoder_data, 0);

#if 1
  // some testcode

  // try insert some random data
  uint8_t x = 0xFF;
  bitvec_insert_bits(&x, 3);
  uint8_t val[4] = { 0xde, 0xad, 0xca, 0xfe }; // expect 0xDEADCAFE
  uint8_t val2[4] = { 0xFF, 0xFF, 0xFF, 0xF1 }; // expect 0xFFFFFF11
  uint8_t val3[4] = { 0xCD, 0x03 }; // expect 0x01CD
  uint8_t val4[17] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17 };
  bitvec_insert_bits(val3, 9);
  bitvec_insert_bits(val2, 32-4+1);
  bitvec_insert_bits(val, 32);
  bitvec_insert_bits(val4, 17*8);

  // copy data to decoder and reinit
  uint32_t encoded_size_bits = bitvec_get_encoded_nbits();
  memcpy(decoder_data, encoder_data, UZIP_CODEC_BUF_SIZE);
  bitvec_init(decoder_data, encoded_size_bits);

  // try extract same random data

  uint8_t test32[20] = { 0 };

  memset(test32, 0, sizeof(test32));
  bitvec_extract_bits(test32, 17*8);
  uint32_t i;
  for (i = 0; i < sizeof(val4); i++) {
    printf("%d\n", test32[i]);
  }

  memset(test32, 0, sizeof(test32));
  bitvec_extract_bits(test32, 32);
  printf("test32 = %02x %02x %02x %02x\n", test32[0], test32[1], test32[2], test32[3]);

  memset(test32, 0, sizeof(test32));
  bitvec_extract_bits(test32, 32-4+1);
  printf("test32 = %02x %02x %02x %02x\n", test32[0], test32[1], test32[2], test32[3]);

  memset(test32, 0, sizeof(test32));
  bitvec_extract_bits(test32, 9);
  printf("test32 = %02x %02x %02x %02x\n", test32[0], test32[1], test32[2], test32[3]);
#endif //test

#if 0
 exit_main:
  if (ret == EXIT_FAILURE) {
    fprintf(stderr, "exit: error %d, %s\n", errno, strerror(errno));
  }
#endif

  return ret;
}
