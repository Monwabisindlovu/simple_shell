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
char *start; /* Start of the current token */
char *end; /* End of the current token */
int state; /* Current state of the character type */

tokens = malloc(buffer_size * sizeof(char *));
if (tokens == NULL)
{
perror("split_line");
exit(EXIT_FAILURE);
}

start = end = line; /* Initialize start and end pointers to the input line */

while (*end != '\0') /* Loop until the end of the input line */
{
state = 0; /* Initialize state to 0 (normal) */

if (*end == '"') /* If the character is a double quote */
{
state = 1; /* Change state to 1 (double quote) */
end++; /* Move to the next character */
while (*end != '\0' && *end != '"') /* Loop until the end of the input line or another double quote */
{
if (*end == '\\') /* If the character is a backslash */
{
end++; /* Move to the next character */
if (*end == '\0') /* If the end of the input line is reached */
break; /* Break out of the loop */
}
end++; /* Move to the next character */
}
if (*end == '"') /* If the character is a double quote */
end++; /* Move to the next character */
}
else if (*end == '\'') /* If the character is a single quote */
{
state = 2; /* Change state to 2 (single quote) */
end++; /* Move to the next character */
while (*end != '\0' && *end != '\'') /* Loop until the end of the input line or another single quote */
{
if (*end == '\\') /* If the character is a backslash */
{
end++; /* Move to the next character */
if (*end == '\0') /* If the end of the input line is reached */
break; /* Break out of the loop */
}
end++; /* Move to the next character */
}
if (*end == '\'') /* If the character is a single quote */
end++; /* Move to the next character */
}
else if (*end == '#') /* If the character is a comment symbol */
{
state = 3; /* Change state to 3 (comment) */
break; /* Break out of the loop and ignore the rest of the input line */
}
else if (strchr(TOKEN_DELIMITERS, *end) != NULL) /* If the character is a delimiter */
{
state = 4; /* Change state to 4 (delimiter) */

if (start != end) /* If there is a token before the delimiter */
{
token = malloc((end - start + 1) * sizeof(char)); /* Allocate memory for the token */
if (token == NULL)
{
perror("split_line");
exit(EXIT_FAILURE);
}
strncpy(token, start, end - start); /* Copy the token from start to end pointers */
token[end - start] = '\0'; /* Add a null terminator at the end of the token */

tokens[token_count] = token; /* Store the token in the tokens array */
token_count++; /* Increment the token count */

if (token_count >= buffer_size) /* If the buffer size is exceeded */
{
buffer_size *= 2; /* Double the buffer size */
tokens = realloc(tokens, buffer_size *sizeof(char *)); /* Reallocate memory for the tokens array */

if (tokens == NULL) /* If memory allocation fails */
{
perror("split_line");
exit(EXIT_FAILURE);
}
}
}

start = end + 1; /* Move the start pointer to the next character after the delimiter */
end++; /* Move the end pointer to the next character */
}
else /* If the character is a normal character */
{
end++; /* Move the end pointer to the next character */
}

if (*end == '\0' && state != 3) /* If the end of the input line is reached and it is not a comment */
{
token = malloc((end - start + 1) * sizeof(char)); /* Allocate memory for the last token */
if (token == NULL)
{
perror("split_line");
exit(EXIT_FAILURE);
}
strncpy(token, start, end - start); /* Copy the token from start to end pointers */
token[end - start] = '\0'; /* Add a null terminator at the end of the token */

tokens[token_count] = token; /* Store the token in the tokens array */
token_count++; /* Increment the token count */

if (token_count >= buffer_size) /* If the buffer size is exceeded */
{
buffer_size *= 2; /* Double the buffer size */
tokens = realloc(tokens, buffer_size *sizeof(char *)); /* Reallocate memory for the tokens array */

if (tokens == NULL) /* If memory allocation fails */
{
perror("split_line");
exit(EXIT_FAILURE);
}
}
}
}

tokens[token_count] = NULL; /* Add a null pointer at the end of the tokens array */
return (tokens);
}

