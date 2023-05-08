#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void add(int8_t *a, int8_t *b, int16_t *ans) {
  for (int i = 0; i < 100; ++i) {
    ans[i] = a[i] + b[i];
  }
}

void sub(int16_t *a, int8_t *b, int16_t *ans) {
  for (int i = 0; i < 200; ++i) {
    if (i > 99) {
      ans[i] = a[i];
    }
    else {
        ans[i] = a[i] - b[i];
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

int get_random_int(int min, int max) {
  return min + (int)(rand() / (1.0 + RAND_MAX) * (max - min + 1.0));
}

void mul(int8_t *a, int8_t *b, int16_t *ans) {
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      ans[i + j] += a[i] * b[j];
    }
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
