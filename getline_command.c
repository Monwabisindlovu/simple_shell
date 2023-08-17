#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _getline_command - Read a line of input from the user.
 * Return: A pointer to the allocated buffer containing the input line.
 */
char *_getline_command(void)
{
char *line = NULL;
size_t bufsize = 0;


ssize_t read = getline(&line, &bufsize, stdin);

if (read == -1)
{

if (feof(stdin))
{
free(line);
return (NULL);
}
else
{
perror("getline");
free(line);
exit(EXIT_FAILURE);
}
}

return (line);
}
