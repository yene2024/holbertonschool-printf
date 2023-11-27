#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
int printChar(int c);
int printStr(char *str);
int printDigit(long n, int base);
int specChecker(char spec, va_list ap);
int _printf(const char *format, ...);
#endif
