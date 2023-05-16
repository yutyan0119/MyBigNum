#include <stdint.h>

#include "add_sub.h"
#include "carry_up_down.h"
#include "div_by.h"
#include "memcpy.h"
#include "mul.h"

#pragma once

// test passed
void divider(short *k, short *kinv) {
  short x[128] = {0};
  x[126] = 5;
  for (int i = 0; i < 20; ++i) {
    short bignum[256] = {0};
    bignum[255] = 1;
    short tmp[256] = {0};
    mul(k, x, tmp);
    sub256(bignum, tmp, tmp);
    short tmp2[384] = {0};
    mul384(tmp, x, tmp2);
    short tmp3[128] = {0};
    div_by_10n384(tmp2, 255, tmp3);
    add(x, tmp3, x);
    // print_array(x, 128);
  }
  mymemcpy(kinv, x, sizeof(short) * 128);
}