#include <stdint.h>  //int16_t
#include <stdio.h>   //printf
#include <stdlib.h>  //calloc and free

#include "add_sub.h"
#include "carry_up_down.h"
#include "divider.h"
#include "memcpy.h"
#include "mul.h"
#include "mypow.h"
#include "print.h"
#include "sqrt.h"

int main() {
  int16_t* a = calloc(128, sizeof(int16_t));
  a[127] = 1;
  int16_t* b = calloc(128, sizeof(int16_t));
  b[126] = 5;
  int16_t* c = calloc(128, sizeof(int16_t));
  int16_t** two_n = calloc(9, sizeof(int16_t*));
  for (int i = 0; i < 9; ++i) {
    two_n[i] = calloc(128, sizeof(int16_t));
  }
  for (int i = 0; i < 9; ++i) {
    two_n[i][0] = mypow(2, i + 1);
    carry_up_down_fix128(two_n[i]);
  }
  sub(a, b, c);
  int16_t** clist = calloc(10, sizeof(int16_t*));
  for (int i = 0; i < 10; ++i) {
    clist[i] = calloc(128, sizeof(int16_t));
  }
  mymemcpy(clist[0], c, sizeof(int16_t) * 128);
  for (int i = 0; i < 9; ++i) {
    int16_t ab[256] = {0};
    mul(a, b, ab);
    int16_t sqrtab[128] = {0};
    my_sqrt(ab, sqrtab);
    int16_t aplusb[128] = {0};
    add(a, b, aplusb);
    div_2(aplusb);
    int16_t an[128] = {0};
    add(aplusb, sqrtab, an);
    div_2(an);
    int16_t bn[128] = {0};
    mymemcpy(bn, sqrtab, sizeof(int16_t) * 128);
    int16_t cn[128] = {0};
    sub(an, bn, cn);
    int16_t tmp2[256] = {0};
    mul(cn, two_n[i], tmp2);
    mymemcpy(a, an, sizeof(int16_t) * 128);
    mymemcpy(b, bn, sizeof(int16_t) * 128);
    mymemcpy(clist[i + 1], tmp2, sizeof(int16_t) * 128);
  }
  int16_t k[128] = {0};
  for (int i = 0; i < 10; ++i) {
    add(k, clist[i], k);
  }
  int16_t onetwoeight[128] = {0};
  onetwoeight[127] = 1;
  sub(onetwoeight, k, k);
  for (int i = 126; i >= 0; --i) {
    k[i + 1] = k[i];
  }
  int16_t kinv[128] = {0};
  divider(k, kinv);
  int16_t aplusb[128] = {0};
  add(a, b, aplusb);
  int16_t ans[256] = {0};
  mul(aplusb, kinv, ans);
  print_array(ans, 256);
  free(a);
  free(b);
  free(c);
  for (int i = 0; i < 9; ++i) {
    free(two_n[i]);
  }
  free(two_n);
  for (int i = 0; i < 10; ++i) {
    free(clist[i]);
  }
  free(clist);
  return 0;
}
