#include "carry_up_down.h"
#pragma once

// test passed
void add(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 128; ++i) {
    ans[i] = a[i] + b[i];
  }
  carry_up_down_fix128(ans);
}

// test passed
void add256(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 256; ++i) {
    ans[i] = a[i] + b[i];
  }
  carry_up_down_fix(ans);
}

// test passed
void sub(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 128; ++i) {
    ans[i] = a[i] - b[i];
  }
  carry_up_down_fix128(ans);
}

void sub256(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 256; ++i) {
    ans[i] = a[i] - b[i];
  }
  carry_up_down_fix(ans);
}

void sub384(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 384; ++i) {
    ans[i] = a[i] - b[i];
  }
  carry_up_down_fix384(ans);
}
