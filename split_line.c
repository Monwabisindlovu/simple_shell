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
	size_t buffer_size = BUFSIZE;
	char **tokens = malloc(sizeof(char *) * buffer_size);
	char *token = strtok(line, TOKEN_DELIMITERS);

	if (tokens == NULL)
	{
		perror("split_line");
		exit(EXIT_FAILURE);
	}


	while (token != NULL)
	{
		tokens[token_count] = strdup(token);

		if (tokens[token_count] == NULL)
		{
			perror("split_line");
			exit(EXIT_FAILURE);
		}

		token_count++;

		if (token_count >= buffer_size)
		{
			buffer_size += BUFSIZE;
			tokens = realloc(tokens, sizeof(char *) * buffer_size);
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
