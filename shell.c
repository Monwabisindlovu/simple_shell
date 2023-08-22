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
		args = split_line(line);

		if (args[0] != NULL)
		{
			status = execute(args);
		}
		else
		{
			status = 1;
		}

		free(line);
		free(args);
	} while (status);

	return 0;
}
