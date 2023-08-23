#include "shell.h"

/**
 *split_line - Split a line into tokens.
 *
 *@line: The input line to be split.
 *Return: An array of pointers to tokens, or NULL if memory allocation fails.
 */
char **split_line(char *line)
{
	size_t i = 0;
	size_t token_count = 0;
	size_t token_size = 10;
	char **tokens = malloc(token_size* sizeof(char*));
	char *token = strtok(line, TOKEN_DELIMITERS);

	if (token == NULL)
	{
		return (NULL);
	}

	while (token != NULL)
	{
		if (token_count >= token_size)
		{
			token_size *= 2;
			tokens = realloc(tokens, token_size* sizeof(char*));
			if (tokens == NULL)
			{
				perror("split_line");
				exit(EXIT_FAILURE);
			}
		}

		tokens[token_count] = strdup(token);
		if (tokens[token_count] == NULL)
		{
			perror("split_line");
			exit(EXIT_FAILURE);
		}

		token_count++;
		token = strtok(NULL, TOKEN_DELIMITERS);
	}

	tokens[token_count] = NULL;
	for (i = 0; i < token_count; i++)
	{
		free(tokens[i]);
	}

	free(tokens);
	return (tokens);
}
