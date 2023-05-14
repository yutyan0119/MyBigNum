#include "add_sub.h"
#include "carry_up_down.h"
#include "div_by.h"
#include "mul.h"
#include "print.h"

#pragma once

//多分ok
void my_sqrt(int16_t *in, int16_t *ans) {
  int16_t x[128] = {0};
  x[124] = 5;
  int16_t a[128] = {0};
  div_by_10n(in, 127, a);
  for (int i = 0; i < 30; ++i) {
    int16_t one384[384] = {0};
    one384[379] = 1;
    int16_t tmp[256] = {0};
    mul(a, x, tmp);
    int16_t tmp2[384] = {0};
    mul384(tmp, x, tmp2);
    sub384(one384, tmp2, tmp2);
    int16_t tmp3[512] = {0};
    mul512(tmp2, x, tmp3);
    int16_t tmp4[128] = {0};
    div_by_10n512(tmp3, 379, tmp4);
    div_2(tmp4);
    int16_t tmp5[128] = {0};
    add(x, tmp4, tmp5);
    memcpy(x, tmp5, sizeof(int16_t) * 128);
  }
  int16_t tmp[256] = {0};
  mul(a, x, tmp);
  carry_up_down_fix(tmp);
  div_by_10n(tmp, 126, ans);
}