#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

int print_string(va_list args, int *count);
int print_char(va_list args, int *count);
int print_int(va_list args, int *count);
int print_rev(va_list args, int *count);

/**
 * _printf - Custom printf function, calls other functions.
 * @format: Format string containing conversion specifiers
 * Return: Number of characters printed (excluding null byte)
 */

int _printf(const char *format, ...)
{
	int count = 0;
	va_list args;

	if (!format)
	{
		return (-1);
	}

	va_start(args, format);

	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			int (*handlers[256])(va_list, int *) = { NULL };
			handlers[(unsigned char)('s')] = print_string;
			handlers[(unsigned char)('c')] = print_char;
			handlers[(unsigned char)('d')] = handlers[(unsigned char)('i')] = print_int;
			handlers[(unsigned char)('r')] = print_rev;

			if (handlers[(unsigned char)(*(format + 1))])
			{
				handlers[(unsigned char)(*(format + 1))](args, &count);
				format += 2;
			}
			else
			{
				write(1, format, 1);
				count++;
				format++;
			}
		}
		else
		{
			write(1, format, 1);
			count++;
			format++;
		}
	}
	va_end(args);
	return (count);
}

/**
 * print_string - function to print a string
 * @args: va_list containing variable arguments
 * @count: Pointer to the count of characters printed
 * Return: Count of characters printed
 */

int print_string(va_list args, int *count)
{
	char *str = va_arg(args, char *);

	while (*str)
	{
		write(1, str++, 1);
		(*count)++;
	}
	return (*count);
}

/**
 * print_char - function to print a character
 * @args: va_list containing variable arguments
 * @count: Pointer to the count of characters printed
 * Return: Count of characters printed
 */

int print_char(va_list args, int *count)
{
	char c = va_arg(args, int);

	write(1, &c, 1);
	(*count)++;
	return (*count);
}

/**
 * print_int - print an integer
 * @args: va_list containing variable arguments
 * @count: Pointer to the count of characters printed
 * Return: Count of characters printed
 */

int print_int(va_list args, int *count)
{
	int num = va_arg(args, int);
	char buffer[20];
	int len = 0;

	if (num < 0)
	{
		write(1, "-", 1);
		(*count)++;
		num = -num;
	}

	do {
		buffer[len++] = num % 10 + '0';
	} while (num /= 10);

	while (len)
	{
		write(1, &buffer[--len], 1);
		(*count)++;
	}
	return (*count);
}

/**
 * print_rev - Print a string in reverse.
 * @args: va_list containing variable arguments
 * @count: Pointer to the count of characters printed
 * Return: Count of characters printed
 */

int print_rev(va_list args, int *count)
{
	char *str = va_arg(args, char *);
	int len = 0;

	if (!str)
		str = "(null)";

	while (str[len])
		len++;

	while (len > 0)
	{
		if (str[len - 1] != '\n')
		{
			write(1, &str[--len], 1);
			(*count)++;
		}
		else
		{
			len--;
		}
	}
	return (*count);
}
