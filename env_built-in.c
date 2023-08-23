#include "shell.h"

/**
 *print_environment - Print environment variables.
 *
 *Return: Always returns 1 to continue shell loop.
 */
int print_environment(void)
{
	char **env = environ;
	ssize_t len = strlen(*env);

	while (*env != NULL)
	{
		if (write(STDOUT_FILENO, *env, len) != len)
		{
			perror("write");
			return (0);
		}

		if (write(STDOUT_FILENO, "\n", 1) != 1)
		{
			perror("write");
			return (0);
		}

		env++;
	}

	return (1);
}
