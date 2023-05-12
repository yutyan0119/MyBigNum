#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mul.h"
#include "print.h"

#pragma once

//test passed
void div_by_10n(int16_t *a, int n, int16_t *ans) {
  for (int i = n; i < 256; ++i) {
    ans[i - n] = a[i];
  }
}

//test passed
void div_by_10n384(int16_t *a, int n, int16_t *ans) {
  for (int i = n; i < 384; ++i) {
    ans[i - n] = a[i];
  }
}

//test passed
void div_by_10n512(int16_t *a, int n, int16_t *ans) {
  for (int i = n; i < 512; ++i) {
    ans[i - n] = a[i];
  }
}

//test passed
void div_2(int16_t *a) {
  int16_t tmp[256] = {0};
  int16_t five[128] = {0};
  five[0] = 5;
  mul(a, five, tmp);
  div_by_10n(tmp, 1, a);
}