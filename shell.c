#include "shell.h"

/**
 * main - Entry point of the command-line interpreter.
 *
 * This function implements a simple interactive shell-like
 * loop where it continuously
 * prompts the user for input, reads the provided command line,
 * tokenizes it into arguments,
 * and then executes the corresponding command.
 * The loop repeats indefinitely until the user
 * chooses to exit the shell.
 *
 * Return: Always returns 0 to indicate successful program execution.
 */

int main(void)
{
	char *line;
	char **args;
	int i;

	while (1)
	{
		print_prompt();
		line = read_line();

		if (!line)
			break;

		if (strlen(line) > 0)
		{
			args = malloc(MAX_INPUT_SIZE * sizeof(char *));
			i = 0;
			args[i] = strtok(line, " \n");

			while (args[i] != NULL)
			{
				i++;
				args[i] = strtok(NULL, " \n");
			}

			args[i] = NULL;

			execute_command(args);

			free(args);
		}

		free(line);
	}

	return (0);
}
