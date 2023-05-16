#include "add_sub.h"
#include "carry_up_down.h"
#include "div_by.h"
#include "mul.h"
#include "print.h"

#pragma once

// 多分ok
void my_sqrt(short *in, short *ans) {
  short x[128] = {0};
  x[124] = 5;
  short a[128] = {0};
  div_by_10n(in, 127, a);
  for (int i = 0; i < 30; ++i) {
    short one384[384] = {0};
    one384[379] = 1;
    short tmp[256] = {0};
    mul(a, x, tmp);
    short tmp2[384] = {0};
    mul384(tmp, x, tmp2);
    sub384(one384, tmp2, tmp2);
    short tmp3[512] = {0};
    mul512(tmp2, x, tmp3);
    short tmp4[128] = {0};
    div_by_10n512(tmp3, 379, tmp4);
    div_2(tmp4);
    short tmp5[128] = {0};
    add(x, tmp4, tmp5);
    mymemcpy(x, tmp5, sizeof(short) * 128);
  }
  short tmp[256] = {0};
  mul(a, x, tmp);
  carry_up_down_fix(tmp);
  div_by_10n(tmp, 126, ans);
}