#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

int print_chars(va_list args, int *count, int is_char);
int print_int(va_list args, int *count);
int print_unsigned(va_list args, int *count, int is_octal);
int print_hex_address(va_list args, int *count);
int _printf(const char *format, ...);

/**
 * print_chars - Function to print characters or strings.
 * @args: va_list containing variable arguments.
 * @count: Pointer to the count of characters printed.
 * @is_char: 1 if printing a character, 0 if printing a string.
 * Return: Count of characters printed
**/

int print_chars(va_list args, int *count, int is_char)
{
	char *str;
	char c;

	if (is_char)
	{
		c = va_arg(args, int);
		if (c == '\0')
		{
			write(1, "(null)", 6);
			*count += 6;
		}
		else
		{
			write(1, &c, 1);
			(*count)++;
		}
	}
	else
	{
		str = va_arg(args, char *);
		if (str == NULL)
		{
			write(1, "(null)", 6);
				*count += 6;
		}
		else
		{
			while (*str)
			{
				write(1, str++, 1);
				(*count)++;
			}
		}
	}
	return (*count);
}

/**
 * print_int - Function that print signed integers.
 * @args: va_list containing variable arguments
 * @count: Pointer to the count of characters printed
 * Return: Count of characters printed
*/

int print_int(va_list args, int *count)
{
	int num = va_arg(args, int), len = 0;
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
	unsigned int num = va_arg(args, unsigned int), len = 0;
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
	uintptr_t address = (uintptr_t)addr;
	int leading_zeros = 0;
	int i = 0;

	if (address == 0)
	{
		write(1, "(nil)", 5);
		(*count) += 5;
		return (*count);
	}

	write(1, "0x", 2);
	*count += 2;

	for (i = 0; i < 16; ++i)
	{
		int digit = (address >> ((15 - i) * 4)) & 0xF;

		if (digit != 0 || leading_zeros)
		{
			char digitChar = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);

			write(1, &digitChar, 1);
			(*count)++;
			leading_zeros = 1;
		}
	}

	return (*count);
}

/**
 * _printf - Custom printf function, calls other functions.
 * @format: Format string containing conversion specifiers
 * Return: Number of characters printed (excluding null byte)
*/
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
				handled = print_unsigned(args, &count, 0);
			else if (specifier == 'o')
				handled = print_unsigned(args, &count, 1);
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
