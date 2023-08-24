#include "shell.h"

/**
 * custom_puts - prints an input string to stderr.
 * @str: the string to be printed.
 *
 * Return: Nothing to the (void custum_puts)
 */
void custom_puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		custom_putchar(str[index]);
		index++;
	}
}

/**
 * custom_putchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success (1).
 * On error, (-1) is returned, and errno is set appropriately.
 */
int custom_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * custom_put_to_fd - writes the character c to given file descriptor.
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success (1).
 * On error, (-1) is returned, and errno is set appropriately.
 */
int custom_put_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * custom_puts_to_fd - prints an input string to the given file descriptor.
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written.
 */
int custom_puts_to_fd(char *str, int fd)
{
	int index = 0;

	if (!str)
		return (0);
	while (*str)
	{
		index += custom_put_to_fd(*str++, fd);
	}

	return (index);
}
