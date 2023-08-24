#include "shell.h"

/**
 * custom_strcpy - copies a string
 * @dest: The destination buffer
 * @src: The source string
 *
 * Return: Pointer to destination buffer
 */
char *custom_strcpy(char *dest, char *src)
{
	int index = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

/**
 * custom_strdup - duplicates a string
 * @str: The string to duplicate
 *
 * Return: Pointer to the duplicated string
 */
char *custom_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);

	for (length++; length--;)
		result[length] = *--str;

	return (result);
}

/**
 * custom_puts - prints a string
 * @str: The string to be printed
 *
 * Return: Nothing
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
 * custom_putchar - writes a character to stdout
 * @c: The character to print
 *
 * Return: On success, returns (1).
 * On error, returns (-1), and errno is set accordingly.
 */
int custom_putchar(char c)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}

	if (c != BUF_FLUSH)
		buffer[index++] = c;

	return (1);
}
