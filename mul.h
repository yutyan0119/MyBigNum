#include "carry_up_down.h"

#pragma once

//test passed
void mul(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 128; ++i) {
    for (int j = 0; j < 128; ++j) {
      ans[i + j] += a[i] * b[j];
    }
  }
  carry_up_down_fix(ans);
}

//test passed
void mul384(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < 128; ++j) {
      ans[i + j] += a[i] * b[j];
    }
  }
  carry_up_down_fix384(ans);
}


//test passed
void mul512(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 384; ++i) {
    for (int j = 0; j < 128; ++j) {
      ans[i + j] += a[i] * b[j];
    }
  }
  carry_up_down_fix512(ans);
}