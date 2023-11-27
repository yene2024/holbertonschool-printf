#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

int print_int(va_list args, int *count);
int _printf(const char *format, ...);

/**
 * print_d_i - Function that print signed integers.
 * @args: va_list containing variable arguments
 * @count: Pointer to the count of characters printed
 * Return: Count of characters printed
 */
int print_d_i(va_list args, int *count)
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
