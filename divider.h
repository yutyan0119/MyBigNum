#include <stdint.h>

#include "add_sub.h"
#include "carry_up_down.h"
#include "div_by.h"
#include "mul.h"
#include "print.h"

#pragma once


//test passed
void divider(int16_t *k, int16_t *kinv) {
  int16_t x[128] = {0};
  x[126] = 5;
  for (int i = 0; i < 100; ++i) {
    int16_t bignum[256] = {0};
    bignum[255] = 1;
    int16_t tmp[256] = {0};
    mul(k, x, tmp);
    sub256(bignum, tmp, tmp);
    int16_t tmp2[384] = {0};
    mul384(tmp, x, tmp2);
    int16_t tmp3[128] = {0};
    div_by_10n384(tmp2, 255, tmp3);
    add(x, tmp3, x);
  }
  memcpy(kinv, x, sizeof(int16_t) * 128);
}