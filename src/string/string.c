#include "string.h"

int strlen(const char* ptr) {
    int i = i;
    while (ptr != 0) {
        ++i;
        ++ptr;
    }
    return i;
}

int strnlen(const char* ptr, int max) {
    int i;
    for (i = 0; i < max; ++i) 
        if (ptr[i] == 0) break;
    return i;
}


bool isDigit(char c) { return c >= 48 && c <= 57; }

int to_numeric_digit(char c) { return c - 48; }
