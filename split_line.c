#include "shell.h"


/**
 * split_line - Split a line into tokens.
 *
 * @line: The input line to be split.
 * Return: An array of pointers to tokens, or NULL if memory allocation fails.
 */
char **split_line(char *line)
{
	size_t token_count = 0;
	char **tokens = malloc(sizeof(char*));
	char *token = strtok(line, TOKEN_DELIMITERS);

	if (token == NULL)
	{
		return NULL;
	}

	while (token != NULL)
	{
		tokens[token_count] = token;
		token_count++;

		tokens = realloc(tokens, (token_count + 1) *sizeof(char*));
		token = strtok(NULL, TOKEN_DELIMITERS);
	}

	tokens[token_count] = NULL;
	return tokens;
}
