#include "shell.h"

/**
 *main - Entry point
 *
 *Return: Always 0
 */
int main(void)
{
	char *line;
	char **args;
	int status;

	do {
		write(STDOUT_FILENO, "($) ", 4);
		line = read_line();
		args = split_line(line);
		status = execute(args[0], args);
		free(line);
		free(args);
	} while (status);

	return (0);
}
