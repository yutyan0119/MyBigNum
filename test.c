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
    const char* str = "45694658104446362537496662254768333661176773001483150839436224726748435807080538559873312100885656393157817473150963778124939960";
    short arr[strlen(str)];
    arr[0] = 0;

    for (size_t i = 0; i < strlen(str) - 1; i++) {
        arr[127-i] = str[i] - '0';  // '0' is subtracted to convert char to int
    }
    print_array(arr, 128);
    // Print to verify
    short k[128] = {0};
    divider(arr, k);
    print_array(k, 128);
    return 0;
}