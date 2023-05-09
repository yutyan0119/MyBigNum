#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int get_random_int(int min, int max) {
  return min + (int)(rand() / (1.0 + RAND_MAX) * (max - min + 1.0));
}

void add(int8_t *a, int8_t *b, int16_t *ans) {
  for (int i = 0; i < 100; ++i) {
    ans[i] = a[i] + b[i];
  }
}

void sub(int16_t *a, int8_t *b, int16_t *ans) {
  for (int i = 0; i < 200; ++i) {
    if (i > 99) {
      ans[i] = a[i];
    } else {
      ans[i] = a[i] - b[i];
    }
  }
}

void mul(int8_t *a, int8_t *b, int16_t *ans) {
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      ans[i + j] += a[i] * b[j];
    }
  }
}

void div(int8_t *a, int len_a, int8_t *b, int len_b, int16_t *ans) {
  if (compare_bigint(a, len_a, b, len_b) < 0) {
    memset(ans, 0, 200 * sizeof(int16_t));
    return;
  }
  int d = len_a - len_b;
  int8_t c[100] = a + d;
  if (compare_bigint(c, len_b, b, len_b) >= 0) {
    ++d;
  }
  if (d == 0) {
    memset(ans, 0, 200 * sizeof(int16_t));
    return;
  }
  for (int i = d - 1; i >= 0; --i) {
    ans[i] = 9;
    for (int j = 1; j <= 9; ++j) {
      int16_t temp[200];
      int8_t mul_b[100] = {0};
      mul_b[0] = j;
      mul(b, mul_b, temp);
      if (compare_bigint(temp, count_digit(temp), c, len_b) == 1){
        ans[i] = j - 1;
        break;
      } 
    }
  }
}

void carry_up_down_fix(int16_t *a) {
  for (int i = 0; i < 200; ++i) {
    if (a[i] >= 10) {
      a[i + 1] += a[i] / 10;
      a[i] -= 10 * (a[i] / 10);
    }
  }
  for (int i = 0; i < 200; ++i) {
    if (a[i] < 0) {
      a[i + 1] -= (-a[i] - 1) / 10 + 1;
      a[i] += 10 * ((-a[i] - 1) / 10 + 1);
    }
  }
}

int compare_bigint(int8_t *a, int len_a, int8_t *b, int len_b) {
  if (len_a > len_b) return +1;
  if (len_a < len_b) return -1;
  for (int i = len_a - 1; i >= 0; --i) {
    if (a[i] > b[i]) return +1;
    if (a[i] < b[i]) return -1;
  }
  return 0;
}

int count_digit(int8_t *a) {
  for (int i = 0; i < 100; ++i) {
    if (a[i] != 0) return 100 - i;
  }
}

int main() {
  srand(time(NULL));
  int8_t a[100];
  for (int i = 0; i < 100; ++i) {
    a[i] = get_random_int(0, 9);
  }
  int8_t b[100];
  for (int i = 0; i < 100; ++i) {
    b[i] = get_random_int(0, 9);
  }
  int16_t *ans = calloc(200, sizeof(int16_t));
  mul(a, b, ans);
  carry_up_down_fix(ans);
  sub(ans, a, ans);
  carry_up_down_fix(ans);
  for (int i = 199; i >= 0; --i) {
    printf("%d ", ans[i]);
  }
  printf("\n");
  for (int i = 99; i >= 0; --i) {
    printf("%d", a[i]);
  }
  printf("\n+\n");
  for (int i = 99; i >= 0; --i) {
    printf("%d", b[i]);
  }
  printf("\n=\n");
  for (int i = 199; i >= 0; --i) {
    printf("%d", ans[i]);
  }
  printf("\n");
  free(ans);
  return 0;
}
