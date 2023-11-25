#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

/**
 * _printf - Custom printf function, calls other functions.
 * @format: Format string containing conversion specifiers
 * @args: Variable arguments list
 * @count: Number of characters printed
 * Return: Number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	int chara_print = 0;
	int count = 0;
	va_list args;

	if (!format)
	{
		return (-1);
	}

	va_start(args, format);

	while (*format)
	{
		if (*format == '%' && (++format))
		{
			int (*handlers[256])(va_list, int *) = { NULL };
			handlers[(unsigned char)'s'] = print_string;
			handlers[(unsigned char)'c'] = print_char;
			handlers[(unsigned char)'d'] = handlers[(unsigned char)'i'] = print_int;

			if (handlers[(unsigned char)(*format)])
			{
				handlers[(unsigned char)(*format)](args, &count);
			}
			else
			{
				write(1, format - 1, 2);
				chara_print += 2;
			}
		}
		else
		{
			write(1, format, 1);
			chara_print++;
			count++;
			format++;
		}
	}
	va_end(args);
	return (count);
}

/**
 * print_string - function to print a string
 * @str: String to be printed
 *
 * Return: count
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
 * @ch: Character to be printed
 *
 * Return: count
 */

int print_char(va_list args, int *count)
{
	char c = va_arg(args, int);

	write(1, &c, 1);
	(*count)++;
	return (*count);
}

/**
 * print_int - function to print an integer
 * @num: Integer to be printed
 *
 * Return: count
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
