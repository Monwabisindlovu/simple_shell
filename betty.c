#include <unistd.h>

/**
 * print_hello - prints "Hello, world!" to the standard output
 * Return: the number of bytes written, or -1 on error
 */
int print_hello(void)
{
char *str = "Hello, world!\n";
int len = 0;

while (str[len])
len++;
return (write(1, str, len));
}

