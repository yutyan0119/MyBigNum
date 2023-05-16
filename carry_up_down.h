#include <stdint.h>

#pragma once

// test passed
void carry_up_down_fix(short *a) {
  for (int i = 0; i < 256; ++i) {
    if (a[i] >= 10) {
      a[i + 1] += a[i] / 10;
      a[i] -= 10 * (a[i] / 10);
    }
  }
  for (int i = 0; i < 256; ++i) {
    if (a[i] < 0) {
      a[i + 1] -= (-a[i] - 1) / 10 + 1;
      a[i] += 10 * ((-a[i] - 1) / 10 + 1);
    }
  }
}

// test passed
void carry_up_down_fix128(short *a) {
  for (int i = 0; i < 128; ++i) {
    if (a[i] >= 10) {
      a[i + 1] += a[i] / 10;
      a[i] -= 10 * (a[i] / 10);
    }
  }
  for (int i = 0; i < 128; ++i) {
    if (a[i] < 0) {
      a[i + 1] -= (-a[i] - 1) / 10 + 1;
      a[i] += 10 * ((-a[i] - 1) / 10 + 1);
    }
  }
}

// test passed
void carry_up_down_fix384(short *a) {
  for (int i = 0; i < 384; ++i) {
    if (a[i] >= 10) {
      a[i + 1] += a[i] / 10;
      a[i] -= 10 * (a[i] / 10);
    }
  }
  for (int i = 0; i < 384; ++i) {
    if (a[i] < 0) {
      a[i + 1] -= (-a[i] - 1) / 10 + 1;
      a[i] += 10 * ((-a[i] - 1) / 10 + 1);
    }
  }
}

// test passed
void carry_up_down_fix512(short *a) {
  for (int i = 0; i < 512; ++i) {
    if (a[i] >= 10) {
      a[i + 1] += a[i] / 10;
      a[i] -= 10 * (a[i] / 10);
    }
  }
  for (int i = 0; i < 512; ++i) {
    if (a[i] < 0) {
      a[i + 1] -= (-a[i] - 1) / 10 + 1;
      a[i] += 10 * ((-a[i] - 1) / 10 + 1);
    }
  }
}