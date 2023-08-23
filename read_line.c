#include <stdlib.h>
#include <string.h>

#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * read_line - Read a line of input from stdin.
 *
 * Return: A pointer to the input line (string),
 * or NULL if end-of-file is reached.
 */
char *read_line(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;

nread = getline(&line, &len, stdin);
if (nread == -1)
{
free(line);
exit(EXIT_SUCCESS);
}

return (line);
}
