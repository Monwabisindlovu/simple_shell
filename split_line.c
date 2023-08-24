#include <stdlib.h>
#include <string.h>

#include "shell.h"

#define TOKEN_DELIMITERS " \t\r\n\a"

/**
 * split_line - Split a line into tokens.
 *
 * @line: The input line to be split.
 * Return: An array of pointers to tokens, or NULL if memory allocation fails.
 */
char **split_line(char *line)
{
size_t token_count = 0;
char **tokens = NULL;
char *token = strtok(line, TOKEN_DELIMITERS);

if (token == NULL)
{
return (NULL);
}

tokens = malloc(sizeof(char *));
if (tokens == NULL)
{
perror("split_line");
exit(EXIT_FAILURE);
}

while (token != NULL)
{
tokens[token_count] = token;
token_count++;

tokens = realloc(tokens, (token_count + 1) * sizeof(char *));
if (tokens == NULL)
{
perror("split_line");
exit(EXIT_FAILURE);
}

token = strtok(NULL, TOKEN_DELIMITERS);
}

tokens[token_count] = NULL;
return (tokens);
}
