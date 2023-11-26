#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int print_chars(va_list args, int *count, int is_char);
int print_int(va_list args, int *count);
int print_unsigned(va_list args, int *count, int is_octal);
int print_hex_address(va_list args, int *count);
int _printf(const char *format, ...);

/**
 * print_chars - Function to print characters or strings.
 * @args: va_list containing variable arguments
 * @count: Pointer to the count of characters printed
 * @is_char: 1 if printing a character, 0 if printing a string
 * Return: Count of characters printed
**/

int print_chars(va_list args, int *count, int is_char)
{
	char *str;
	char c;

	if (is_char)
	{
		c = va_arg(args, int);
		if (c == '%' && ((*count)++, 1))
			write(1, &c, 1);
		write(1, &c, 1);
		(*count)++;
	}
	else
	{
		str = va_arg(args, char *);
		while (*str)
			write(1, str++, 1), (*count)++;
	}

	return (*count);
}

/**
 *print_int - Function to print signed integers.
 *@args: va_list containing variable arguments
 *@count: Pointer to the count of characters printed
 *Return: Count of characters printed
*/

int print_int(va_list args, int *count)
{
	int num = va_arg(args, int);
	int len = 0;
	char buffer[20];

	if (num < 0 && (write(1, "-", 1), 1))
		num = -num;

	do {
		buffer[len++] = num % 10 + '0';
	} while (num /= 10);

	while (len)
		write(1, &buffer[--len], 1), (*count)++;

	return (*count);
}

/**
 * print_unsigned - Function to print unsigned integers.
 * @args: va_list containing variable arguments
 * @count: Pointer to the count of characters printed
 * @is_octal: 1 if printing in octal format, 0 otherwise
 * Return: Count of characters printed
*/

int print_unsigned(va_list args, int *count, int is_octal)
{
	unsigned int num = va_arg(args, unsigned int);
	int len = 0;
	char buffer[20];

	do {
		buffer[len++] = num % (is_octal ? 8 : 10) + '0';
	} while (num /= (is_octal ? 8 : 10));

	while (len)
		write(1, &buffer[--len], 1), (*count)++;

	return (*count);
}

/**
 * print_hex_address - Function to print hexadecimal addresses.
 * @args: va_list containing variable arguments
 * @count: Pointer to the count of characters printed
 * Return: Count of characters printed
*/

int print_hex_address(va_list args, int *count)
{
	void *addr = va_arg(args, void *);
	char buffer[20];

	sprintf(buffer, "%p", addr);
	write(1, buffer, strlen(buffer));
	(*count) += strlen(buffer);
	return (*count);
}


/**
 * _printf - Custom printf function, calls other functions.
 * @format: Format string containing conversion specifiers
 * Return: Number of characters printed (excluding null byte)
**/

int _printf(const char *format, ...)
{
	int count = 0;
	va_list args;

	va_start(args, format);

	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			char specifier = *(format + 1);
			int handled = 0;

			if (specifier == 'c' || specifier == 's')
				handled = print_chars(args, &count, specifier == 'c');
			else if (specifier == 'd' || specifier == 'i')
				handled = print_int(args, &count);
			else if (specifier == 'x' || specifier == 'X' || specifier == 'p')
				handled = print_hex_address(args, &count);
			else if (specifier == 'u')
				handled = print_unsigned int(args, &count, 0);
			else if (specifier == 'o')
				handled = print_unsigned int(args, &count, 1);
			if (handled)
			{
				format += 2;
				continue;
			}
			if (specifier == '%')
			{
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

