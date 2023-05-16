#include <stdint.h>
#include <stdio.h>

#pragma once

void print_array(short *array, int length) {
  for (int i = length - 1; i >= 0; --i) {
    printf("%d", array[i]);
  }
  printf("\n");
}