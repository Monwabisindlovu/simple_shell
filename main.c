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
if (line == NULL)
{
write(STDOUT_FILENO, "\n", 1);
break;
}
args = split_line(line);
status = execute_builtin(args);
if (status == -1)
{
status = execute(args);
}

free(line);
free(args);
} while (status);

return (0);
}

