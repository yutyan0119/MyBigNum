#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "add_sub.h"
#include "carry_up_down.h"
#include "divider.h"
#include "mul.h"
#include "print.h"
#include "sqrt.h"

int get_random_int(int min, int max) {
  return min + (int)(rand() / (1.0 + RAND_MAX) * (max - min + 1.0));
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
    // print_array(ab, 256);
    int16_t sqrtab[128] = {0};
    my_sqrt(ab, sqrtab);
    // print_array(sqrtab, 128);
    int16_t aplusb[128] = {0};
    add(a, b, aplusb);
    carry_up_down_fix(aplusb);
    div_2(aplusb);
    int16_t an[128] = {0};
    add(aplusb, sqrtab, an);
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
  print_array(ans, 256);
  return 0;
}
