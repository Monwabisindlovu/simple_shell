#include "shell.h"

/**
 * custom_strlen - calculates the length of a string
 * @str: The string whose length to calculate
 *
 * Return: The length of the string
 */
int custom_strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);

	while (*str++)
		length++;

	return (length);
}

/**
 * custom_strcmp - compares two strings lexicographically
 * @str1: The first string
 * @str2: The second string
 *
 * Return: Negative if str1 < str2,
 * positive if str1 > str2,
 * zero if str1 == str2
 */
int custom_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * custom_starts_with - checks if a string starts with a specified prefix
 * @str: The string to search
 * @prefix: The prefix to find
 *
 * Return: Address of the character after the prefix in str,
 * or NULL if not found
 */
char *custom_starts_with(const char *str, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *str++)
			return (NULL);

	return ((char *)str);
}

/**
 * custom_strcat - concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *custom_strcat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;

	return (result);
}
