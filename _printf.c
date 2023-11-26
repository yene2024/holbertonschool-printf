#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

int _printf(const char *format, ...);

int print_chars(va_list args, int *count, int is_char) {
    char *str;
    char c;

    if (is_char) {
        c = va_arg(args, int);
        if (c == '%' && ((*count)++, 1))
            write(1, &c, 1);
        else
            write(1, &c, 1);
        (*count)++;
    } else {
        str = va_arg(args, char *);
        while (*str)
            write(1, str++, 1), (*count)++;
    }

    return (*count);
}

int print_int(va_list args, int *count) {
    int num = va_arg(args, int), len = 0;
    char buffer[20];

    if (num < 0 && (write(1, "-", 1), 1))
        num = -num;

    do
        buffer[len++] = num % 10 + '0';
    while (num /= 10);

    while (len)
        write(1, &buffer[--len], 1), (*count)++;

    return (*count);
}

int print_unsigned(va_list args, int *count, int is_octal) {
    unsigned int num = va_arg(args, unsigned int), len = 0;
    char buffer[20];

    do
        buffer[len++] = num % (is_octal ? 8 : 10) + '0';
    while (num /= (is_octal ? 8 : 10));

    while (len)
        write(1, &buffer[--len], 1), (*count)++;

    return (*count);
}

int print_hex_address(va_list args, int *count) {
    void *addr = va_arg(args, void *);
    uintptr_t address = (uintptr_t)addr;

    if (address == 0) {
        write(1, "(nil)", 5);
        *count += 5;
        return *count;
    }

    write(1, "0x", 2);
    *count += 2;

    while (address) {
        int digit = address % 16;
        char digitChar = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        write(1, &digitChar, 1);
        address /= 16;
        (*count)++;
    }

    return (*count);
}

int _printf(const char *format, ...) {
    int count = 0;
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%' && *(format + 1)) {
            char specifier = *(format + 1);
            int handled = 0;

            if (specifier == 'c' || specifier == 's')
                handled = print_chars(args, &count, specifier == 'c');
            else if (specifier == 'd' || specifier == 'i')
                handled = print_int(args, &count);
            else if (specifier == 'x' || specifier == 'X' || specifier == 'p')
                handled = print_hex_address(args, &count);
            else if (specifier == 'u')
                handled = print_unsigned(args, &count, 0);
            else if (specifier == 'o')
                handled = print_unsigned(args, &count, 1);

            if (handled) {
                format += 2;
                continue;
            }

            if (specifier == '%') {
                write(1, "%", 1);
                count++;
                format += 2;
                continue;
            }
        }
        write(1, format, 1);
        count++;
        format++;
    }
    va_end(args);
    return (count);
}
