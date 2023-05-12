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


int main (){
    int16_t a[128] = {0};
    // srand(time(NULL));
    // for (int i = 0; i < 256; ++i) {
    //     a[i] = get_random_int(0, 9);
    // }
    a[126] = 1;
    int16_t b[128] = {0};
    b[125] = 5;
    int16_t c[256] = {0};
    mul(a, b, c);
    print_array(c, 256);
    int16_t d[128] = {0};
    my_sqrt(c, d);
    print_array(d, 128);
    return 0;
}