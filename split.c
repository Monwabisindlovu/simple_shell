#include "shell.h"

/**
 * split_string_words - Splits a string into words using delimiters
 * @str: The input string
 * @delim_str: The delimiter string
 *
 * Return: Pointer to an array of strings, or NULL on failure
 */
char **split_string_words(char *str, char *delim_str)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!delim_str)
		delim_str = " ";
	for (i = 0; str[i] != '\0'; i++)
	{
		if (!is_delimiter(str[i], delim_str) &&
			(is_delimiter(str[i + 1], delim_str) || !str[i + 1]))
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimiter(str[i], delim_str))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], delim_str) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}
	s[j] = NULL;
	return (s);
}

/**
 * split_string_words_alt - Splits a string into words using a single delimiter
 * @str: The input string.
 * @delimiter: The delimiter character
 *
 * Return: Pointer to an array of strings, or (NULL) on failure
 */
char **split_string_words_alt(char *str, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
			(str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;
		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}

	s[j] = NULL;
	return (s);
}
