#include "shell.h"

/**
 * custom_strncpy - Copies a string with a specified length
 * @destination: The destination string
 * @source: The source string
 * @max_length: The maximum number of characters to copy
 *
 * Return: Pointer to the destination string
 */
char *custom_strncpy(char *destination, char *source, int max_length)
{
	int i, j;
	char *dest_ptr = destination;

	i = 0;
	while (source[i] != '\0' && i < max_length - 1)
	{
		destination[i] = source[i];
		i++;
	}

	if (i < max_length)
	{
		j = i;
		while (j < max_length)
		{
			destination[j] = '\0';
			j++;
		}
	}

	return (dest_ptr);
}

/**
 * custom_strncat - Concatenates two strings with a specified length
 * @destination: The destination string
 * @source: The source string
 * @max_length: The maximum number of bytes to use
 *
 * Return: Pointer to the destination string
 */
char *custom_strncat(char *destination, char *source, int max_length)
{
	int i, j;
	char *dest_ptr = destination;

	i = 0;
	while (destination[i] != '\0')
		i++;
	j = 0;
	while (source[j] != '\0' && j < max_length)
	{
		destination[i] = source[j];
		i++;
		j++;
	}

	if (j < max_length)
		destination[i] = '\0';
	return (dest_ptr);
}

/**
 * custom_strchr - Locates a character in a string
 * @str: The string to search
 * @character: The character to locate
 *
 * Return: Pointer to the memory area of the character in str,
 * or NULL if not found.
 */
char *custom_strchr(char *str, char character)
{
	do {
		if (*str == character)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
