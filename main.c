#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int get_random_int(int min, int max) {
  return min + (int)(rand() / (1.0 + RAND_MAX) * (max - min + 1.0));
}

void add(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 128; ++i) {
    ans[i] = a[i] + b[i];
  }
}

void sub(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 128; ++i) {
    ans[i] = a[i] - b[i];
  }
}

void mul(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 128; ++i) {
    for (int j = 0; j < 128; ++j) {
      ans[i + j] += a[i] * b[j];
    }
  }
}

void mul384(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 256; ++i) {
    for (int j = 0; j < 128; ++j) {
      ans[i + j] += a[i] * b[j];
    }
  }
}

void mul512(int16_t *a, int16_t *b, int16_t *ans) {
  for (int i = 0; i < 384; ++i) {
    for (int j = 0; j < 128; ++j) {
      ans[i + j] += a[i] * b[j];
    }
  }
}

void carry_up_down_fix(int16_t *a) {
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

void carry_up_down_fix128(int16_t *a) {
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

void carry_up_down_fix384(int16_t *a) {
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

void carry_up_down_fix512(int16_t *a) {
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

void div_by_10n(int16_t *a, int n, int16_t *ans) {
  for (int i = n; i < 256; ++i) {
    ans[i - n] = a[i];
  }
}

void div_by_10n384(int16_t *a, int n, int16_t *ans) {
  for (int i = n; i < 384; ++i) {
    ans[i - n] = a[i];
  }
}

void div_by_10n512(int16_t *a, int n, int16_t *ans) {
  for (int i = n; i < 512; ++i) {
    ans[i - n] = a[i];
  }
}

void div_2(int16_t *a) {
  int16_t tmp[256];
  int16_t five[128];
  five[0] = 5;
  mul(a, five, tmp);
  div_by_10n(tmp, 1, a);
}

void my_sqrt(int16_t *a, int16_t *ans) {
  int16_t x[128] = {0};
  x[127] = 5;
  for (int i = 0; i < 30; ++i) {
    int16_t one384[384] = {0};
    one384[383] = 1;
    int16_t tmp[256] = {0};
    mul(a, x, tmp);
    carry_up_down_fix(tmp);
    int16_t tmp2[384] = {0};
    mul384(tmp, x, tmp2);
    carry_up_down_fix384(tmp2);
    sub(one384, tmp2, tmp2);
    carry_up_down_fix384(tmp2);
    int16_t tmp3[512] = {0};
    mul512(tmp2, x, tmp3);
    carry_up_down_fix512(tmp3);
    int16_t tmp4[128] = {0};
    div_by_10n512(tmp3, 384, tmp4);
    div_2(tmp4);
    add(x, tmp4, x);
    carry_up_down_fix128(x);
  }
  int16_t tmp[256] = {0};
  mul(a, x, tmp);
  carry_up_down_fix(tmp);
  div_by_10n(tmp, 128, ans);
}

void divider(int16_t *k, int16_t *kinv) {
  int16_t x[128] = {0};
  x[127] = 5;
  for (int i = 0; i < 20; ++i) {
    int16_t bignum[256] = {0};
    bignum[255] = 1;
    int16_t tmp[256] = {0};
    mul(k, x, tmp);
    carry_up_down_fix(tmp);
    sub(bignum, tmp, tmp);
    carry_up_down_fix(tmp);
    int16_t tmp2[384] = {0};
    mul384(tmp, x, tmp2);
    int16_t tmp3[128] = {0};
    div_by_10n384(tmp2, 256, tmp3);
    add(x, tmp3, x);
    carry_up_down_fix128(x);
  }
  memcpy(kinv, x, sizeof(int16_t) * 128);
}

int main() {
  srand(time(NULL));
  int16_t a[128] = {0};
  a[127] = 1;
  int16_t b[128] = {0};
  b[126] = 5;
  int16_t c[128] = {0};
  int16_t two_n[8][128] = {0};
  for (int i = 0; i < 8; ++i) {
    two_n[i][0] = pow(2, i);
    carry_up_down_fix128(two_n[i]);
  }
  sub(a, b, c);
  carry_up_down_fix(c);
  int16_t clist[9][128] = {0};
  for (int i = 0; i < 9; ++i) {
    int16_t ab[256] = {0};
    mul(a, b, ab);
    carry_up_down_fix(ab);
    int16_t sqrtab[128] = {0};
    my_sqrt(ab, sqrtab);
    int16_t aplusb[128] = {0};
    add(a, b, aplusb);
    carry_up_down_fix(aplusb);
    div_2(aplusb);
    int16_t an = {0};
    add(aplusb, sqrtab, an);
    int16_t an[128] = {0};
    div_2(an);
    int16_t bn[128] = {0};
    memcpy(bn, sqrtab, sizeof(int16_t) * 128);
    int16_t cn[128] = {0};
    sub(an, bn, cn);
    carry_up_down_fix(cn);
    int16_t tmp2[256] = {0};
    mul(cn, two_n[i], tmp2);
    memcpy(a, an, sizeof(int16_t) * 128);
    memcpy(b, bn, sizeof(int16_t) * 128);
    memcpy(clist[i], tmp2, sizeof(int16_t) * 128);
  }
  int16_t k[128] = {0};
  for (int i = 0; i < 9; ++i) {
    add(k, clist[i], k);
  }
  carry_up_down_fix(k);
  int16_t onetwoeight[128] = {0};
  onetwoeight[127] = 1;
  sub(onetwoeight, k, k);
  carry_up_down_fix(k);
  int16_t kinv[256] = {0};
  divider(k, kinv);
  int16_t aplusb[128] = {0};
  add(a, b, aplusb);
  carry_up_down_fix128(aplusb);
  int16_t ans[256] = {0};
  mul(aplusb, kinv, ans);
  carry_up_down_fix(ans);
  for (int i = 255; i >= 0; --i) {
    printf("%d", ans[i]);
  }
  return 0;
}
