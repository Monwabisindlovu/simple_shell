#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/**
 * tokenize - Tokenize a string into an array of tokens.
 * @lineptr: Input string to be tokenized.
 * Return: An array of pointers to tokens.
 */
char **tokenize(char *lineptr)
{
int bufsize = TOK_BUFSIZE;
int position = 0;
char **tokens = malloc(bufsize * sizeof(char *));
char *token;

if (!tokens)
{
fprintf(stderr, "tokenize: Allocation error\n");
exit(EXIT_FAILURE);
}

token = strtok(lineptr, TOK_DELIM);
while (token != NULL)
{
tokens[position] = token;
position++;

if (position >= bufsize)
{
bufsize += TOK_BUFSIZE;
tokens = realloc(tokens, bufsize * sizeof(char *));
if (!tokens)
{
fprintf(stderr, "tokenize: Reallocation error\n");
exit(EXIT_FAILURE);
}
}

token = strtok(NULL, TOK_DELIM);
}
tokens[position] = NULL;
return (tokens);
}

