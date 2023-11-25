#ifndef MAIN_H
#define MAIN_H
int _printf(const char *format, ...);
char _putchar(char c);
int print_char(va_list args, int *count);
int print_string(va_list args, int *count);
int print_int(va_list args, int *count);
#endif
