#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include "main.h"

/**
 * int_to_str - Convert an integer to a string
 * @num: The integer to convert
 * @buffer: The buffer to store the result
 *
 * Return: Number of characters written to the buffer
 */
int print_int(int num, char *buffer)
{
    int count = 0;
    int is_negative = 0;
	int i, j;
    if (num < 0)
    {
        is_negative = 1;
        num = -num;
    }

    do
    {
        buffer[count++] = num % 10 + '0';
        num /= 10;
    } while (num != 0);

    if (is_negative)
    {
        buffer[count++] = '-';
    }

    for (i = 0, j = count - 1; i < j; i++, j--)
    {
        char temp = buffer[i];
        buffer[i] = buffer[j];
        buffer[j] = temp;
    }

    return count;
}
