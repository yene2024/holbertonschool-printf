#include "main.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
/**
* printChar - Writes one char to the standard output.
* @c: just a character
* Return: the value of write.
*/
int printChar(int c)
{
	return (write(1, &c, 1));
}

/**
* printStr - Writes a string to the standard output.
* @str: just a string
* Return: the count.
*/
int printStr(char *str)
{
	int count = 0, i = 0;

	if (str == NULL)
	{
		return (write(1, "(null)", 6));
	}

	for (; str[i] != '\0'; i++)
	{
		count += printChar(str[i]);
	}

	return (count);
}

/**
* printDigit - Writes a digit to the standard output.
* @n: number to write
* @base: 10
* Return: the count.
*/
int printDigit(long n, int base)
{
	int count = 0, i = 0, index = 0;
	char *digits = "0123456789";
	char buffer[32];

	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}

	do {
		buffer[index++] = digits[n % base];
		n /= base;
	} while (n > 0);

	for (i = index - 1; i >= 0; i--)
	{
		count += printChar(buffer[i]);
	}

	return (count);
}

/**
* specChecker - Checks which specifier is used and redirects to a function.
* @spec: the character to compare.
* @ap: the argument pointer
* Return: the count.
*/
int specChecker(char spec, va_list ap)
{
	int count = 0;

	if (spec == 'c')
	{
		count += printChar(va_arg(ap, int));
	}
	else if (spec == 's')
	{
		count += printStr(va_arg(ap, char *));
	}
	else if (spec == 'i' || spec == 'd')
	{
		count += printDigit((long)va_arg(ap, int), 10);
	}
	else if (spec == 'x')
	{
		count += printDigit((long)va_arg(ap, int), 16);
	}
	else if (spec == 'o')
	{
		count += printDigit((long)va_arg(ap, int), 8);
	}
	else if (spec != '%')
	{
		count += printChar('%');
		count += printChar(spec);
	}
	else
	{
		count += printChar(spec);
	}
	return (count);
}

/**
* _printf - Prints what you need it to.
* @format: the string
* @..: the arguments
* Return: the count.
*/
int _printf(const char *format, ...)
{
	int count = 0, i = 0;
	va_list ap;

	if (format == NULL)
	{
		return (-1);
	}

	va_start(ap, format);
	for (; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
			{
				return (-1);
			}
			else
			{
				count += specChecker(format[i + 1], ap);
			}
			i++;
		}
		else
		{
			count += write(1, &format[i], 1);
		}
	}
	va_end(ap);
	return (count);
}
