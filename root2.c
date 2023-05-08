#include <stdio.h>

#define FIXED_POINT_FACTOR 1000000000 // 10^9
#define TOLERANCE 1 // corresponds to 10^-9 in the fixed point representation
#define MAX_ITER 1000

long long newton_sqrt_2() {
    long long x = FIXED_POINT_FACTOR; // Initial guess: 1.0
    for (int i = 0; i < MAX_ITER; i++) {
        long long x_next = x - ((x * x / FIXED_POINT_FACTOR - 2 * FIXED_POINT_FACTOR) / (2 * x / FIXED_POINT_FACTOR));
        if (x_next > x - TOLERANCE && x_next < x + TOLERANCE) {
            return x_next;
        }
        x = x_next;
    }
    return x;
}

int main() {
    long long sqrt_2_fixed = newton_sqrt_2();
    printf("sqrt(2) = %lld.%09lld\n", sqrt_2_fixed / FIXED_POINT_FACTOR, sqrt_2_fixed % FIXED_POINT_FACTOR);
    return 0;
}