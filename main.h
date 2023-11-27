#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
int print_chars(va_list args, int *count, int is_char);
int print_int(va_list args, int *count);
int print_unsigned(va_list args, int *count, int is_octal);
int print_hex_address(va_list args, int *count);
int _printf(const char *format, ...);

#endif
