#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

/**
 * _printf - Custom printf function
 * @format: Format string containing conversion specifiers
 *
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
    int chara_print = 0;
    int count = 0;
    va_list list_of_args;

    if (format == NULL)
    {
        return (-1);
    }

    va_start(list_of_args, format);

    while (*format)
    {
        if (*format != '%' || (*(format + 1) == '%' && format++))
        {
            write(1, format, 1);
            chara_print++;
            count++;
        }
        else if (*(format + 1) == 'c')
        {
            char c = va_arg(list_of_args, int);
            write(1, &c, 1);
            chara_print++;
            count++;
            format++;
        }
        else if (*(format + 1) == 's')
        {
            char *str = va_arg(list_of_args, char*);
            int str_len = 0;

            while (str[str_len] != '\0')
            {
                write(1, &str[str_len], 1);
                chara_print++;
                count++;
                str_len++;
            }
            format++;
        }
        format++;
    }

    va_end(list_of_args);
    return count;
}
