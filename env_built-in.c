#include "shell.h"

/**
 *shell_env - Print environment variables.
 *
 *Return: Always returns 1 to continue shell loop.
 */
void print_environment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		size_t len = strlen(*env);

		write(STDOUT_FILENO, *env, len);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
