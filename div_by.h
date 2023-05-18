#include <stdint.h>

#include "memset.h"
#include "mul.h"

#pragma once

//test passed
void div_by_10n(short *a, int n, short *ans) {
  for (int i = n; i < 256; ++i) {
    ans[i - n] = a[i];
  }
}

//test passed
void div_by_10n384(short *a, int n, short *ans) {
  for (int i = n; i < 384; ++i) {
    ans[i - n] = a[i];
  }
}

//test passed
void div_by_10n512(short *a, int n, short *ans) {
  for (int i = n; i < 512; ++i) {
    ans[i - n] = a[i];
  }
}

//test passed
void div_2(short *a) {
  short tmp[256];
  memset(tmp, 0, 256);
  short five[128];
  memset(five, 0, 128);
  five[0] = 5;
  mul(a, five, tmp);
  div_by_10n(tmp, 1, a);
}