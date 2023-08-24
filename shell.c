#include "shell.h"

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
char *line;
char **args;
int status;

do {
write(STDOUT_FILENO, "$ ", 2);
line = read_line();
if (line == NULL) /* Check if end-of-file is reached */
{
write(STDOUT_FILENO, "\n", 1); /* Print a new line */
break; /* Break out of the loop */
}
if (line[0] == '\0' || _isblank(line))
{
/* Empty line or end-of-file */
free(line);
continue;
}
args = split_line(line);
status = execute(args);

free(line);
free(args);
} while (status);

return (0);
}

