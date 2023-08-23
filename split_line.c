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
	size_t tokens_size = 1;
	char **tokens = malloc(sizeof(char *));
	char *token = strtok(line, TOKEN_DELIMITERS);

	if (token == NULL)
	{
		perror("split_line");
		exit(EXIT_FAILURE);
	}

	while (token != NULL)
	{
		tokens[token_count] = token;
		token_count++;

		if (token_count >= tokens_size)
		{
			tokens_size *= 2;
			tokens = realloc(tokens, tokens_size * sizeof(char *));
			if (tokens == NULL)
			{
				perror("split_line");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, TOKEN_DELIMITERS);
	}

	tokens[token_count] = NULL;
	return (tokens);
}
