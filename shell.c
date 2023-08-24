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
if (line == NULL || line[0] == '\0' || _isblank(line))
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

/**
 * _isblank - Check if a string contains only spaces.
 *
 * @str: The string to check.
 * Return: 1 if true, 0 if false.
 */
int _isblank(char *str)
{
int i;

for (i = 0; str[i]; i++)
{
if (str[i] != ' ')
return (0);
}
return (1);
}
