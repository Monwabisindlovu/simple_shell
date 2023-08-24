#include "shell.h"

/**
 * check_interactive - Checks if the Shell is in interactive mode
 * @info: Pointer to the info structure.
 *
 * Return: (1) if interactive mode, (0) otherwise
 */
int check_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimi - Checks if character is a delimiter
 * @c: The character to check.
 * @delimi: The delimiter in string.
 *
 * Return: (1) if true, (0) if false.
 */
int is_delimi(char c, char *delimi)
{
	while (*delimi)
		if (*delimi++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - Checks for alphabetic character
 * @c: The character needed to check
 *
 * Return: (1) if "c" is alphabetic, (0) otherwise
 */
int is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * string_to_int - Converts a string to an integer
 * @s: The string to be converted
 *
 * Return: (0) if no numbers in string, converted number otherwise
 */
int string_to_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	output = (sign == -1) ? -result : result;

	return (output);
}
