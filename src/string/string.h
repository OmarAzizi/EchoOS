#ifndef __STRING_H__
#define __STRING_H__

#include <stdbool.h>

int strlen(const char*);
int strnlen(const char*, int);
bool isDigit(char);
int to_numeric_digit(char);

#endif
