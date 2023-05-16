short mypow(short x, short y) {
    short result = 1;
    for (short i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}
