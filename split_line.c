#include <stdlib.h>
#include <string.h>

#include "shell.h"

#define TOKEN_DELIMITERS " \t\r\n\a"
#define INITIAL_BUFSIZE 64

/**
 * split_line - Split a line into tokens.
 *
 * @line: The input line to be split.
 * Return: An array of pointers to tokens, or NULL if memory allocation fails.
 */
char **split_line(char *line)
{
size_t token_count = 0;
size_t buffer_size = INITIAL_BUFSIZE;
char **tokens = NULL;
char *token;

tokens = malloc(buffer_size * sizeof(char *));
if (tokens == NULL)
{
perror("split_line");
exit(EXIT_FAILURE);
}

token = strtok(line, TOKEN_DELIMITERS);

while (token != NULL)
{
tokens[token_count] = token;
token_count++;

if (token_count >= buffer_size)
{
buffer_size *= 2;
tokens = realloc(tokens, buffer_size *sizeof(char *));

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
