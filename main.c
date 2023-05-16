// #include <stdint.h>  //short
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
  short* a = calloc(128, sizeof(short));
  a[127] = 1;
  short* b = calloc(128, sizeof(short));
  b[126] = 5;
  short* c = calloc(128, sizeof(short));
  short** two_n = calloc(9, sizeof(short*));
  for (int i = 0; i < 9; ++i) {
    two_n[i] = calloc(128, sizeof(short));
  }
  for (int i = 0; i < 9; ++i) {
    two_n[i][0] = mypow(2, i + 1);
    carry_up_down_fix128(two_n[i]);
  }
  sub(a, b, c);
  short** clist = calloc(10, sizeof(short*));
  for (int i = 0; i < 10; ++i) {
    clist[i] = calloc(128, sizeof(short));
  }
  mymemcpy(clist[0], c, sizeof(short) * 128);
  for (int i = 0; i < 9; ++i) {
    short ab[256] = {0};
    mul(a, b, ab);
    short sqrtab[128] = {0};
    my_sqrt(ab, sqrtab);
    short aplusb[128] = {0};
    add(a, b, aplusb);
    div_2(aplusb);
    short an[128] = {0};
    add(aplusb, sqrtab, an);
    div_2(an);
    short bn[128] = {0};
    mymemcpy(bn, sqrtab, sizeof(short) * 128);
    short cn[128] = {0};
    sub(an, bn, cn);
    short tmp2[256] = {0};
    mul(cn, two_n[i], tmp2);
    mymemcpy(a, an, sizeof(short) * 128);
    mymemcpy(b, bn, sizeof(short) * 128);
    mymemcpy(clist[i + 1], tmp2, sizeof(short) * 128);
  }
  short k[128] = {0};
  for (int i = 0; i < 10; ++i) {
    add(k, clist[i], k);
  }
  short onetwoeight[128] = {0};
  onetwoeight[127] = 1;
  sub(onetwoeight, k, k);
  for (int i = 126; i >= 0; --i) {
    k[i + 1] = k[i];
  }
  short kinv[128] = {0};
  divider(k, kinv);
  short aplusb[128] = {0};
  add(a, b, aplusb);
  short ans[256] = {0};
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
