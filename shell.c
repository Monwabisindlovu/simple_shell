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
if (isatty(STDIN_FILENO))
{
write(STDOUT_FILENO, "$ ", 2);
}
line = read_line();
if (line == NULL)
{
break;
}
args = split_line(line);
if (strcmp(args[0], "exit") == 0)
{
free(line);
free(args);
exit(0);
}
status = execute(args);

free(line);
free(args);
} while (status);

return (0);
}
