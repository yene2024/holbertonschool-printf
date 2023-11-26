# holbertonschool-printf

README.md

_printf Function:

The _printf function is designed to produce output according to a specific format.
 It mimics the behavior of the standard C library function printf but is simplified 
to handle a subset of conversion specifiers.

Prototype:

c

int _printf(const char *format, ...);

Returns:

The function returns the number of characters printed (excluding the null byte used 
to end output to strings).

Output:

The output is written to stdout, the standard output stream.

Format String Directives:

The format parameter is a character string composed of zero or more directives.
 The following conversion specifiers are supported:

    %c: Single character
    %s: String of characters
    %%: Literal percent sign
    %d or %i: Integer

Limitations:

    Flag characters are not handled.
    Field width is not handled.
    Precision is not handled.
    Length modifiers are not handled.

Contributors:

    Yeneishla Santiago
    Yahsai Santana
