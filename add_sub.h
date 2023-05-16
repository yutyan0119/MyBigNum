#include "carry_up_down.h"
#pragma once

// test passed
void add(short *a, short *b, short *ans) {
  for (int i = 0; i < 128; ++i) {
    ans[i] = a[i] + b[i];
  }
  carry_up_down_fix128(ans);
}

// test passed
void add256(short *a, short *b, short *ans) {
  for (int i = 0; i < 256; ++i) {
    ans[i] = a[i] + b[i];
  }
  carry_up_down_fix(ans);
}

// test passed
void sub(short *a, short *b, short *ans) {
  for (int i = 0; i < 128; ++i) {
    ans[i] = a[i] - b[i];
  }
  carry_up_down_fix128(ans);
}

void sub256(short *a, short *b, short *ans) {
  for (int i = 0; i < 256; ++i) {
    ans[i] = a[i] - b[i];
  }
  carry_up_down_fix(ans);
}

void sub384(short *a, short *b, short *ans) {
  for (int i = 0; i < 384; ++i) {
    ans[i] = a[i] - b[i];
  }
  carry_up_down_fix384(ans);
}
