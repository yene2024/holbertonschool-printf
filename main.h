#ifndef MAIN_H
#define MAIN_H
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>
int printChar(int c);
int printStr(char *str);
int printDigit(long n, int base);
int specChecker(char spec, va_list ap);
int _printf(const char *format, ...);
#endif
