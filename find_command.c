#include "shell.h"

/**
 * find_command - Find the full path of a command in the PATH environment.
 *
 * @command: The name of the command to search for.
 * Return: The full path of the command,
 * or NULL if not found in PATH.
 */
char *find_command(char *command)
{
	char *cmd_path = NULL;
	char *path_env = getenv("PATH");
	char *path_dirs = strdup(path_env);
	char *dir = strtok(path_dirs, ":");

	if (path_env != NULL)
	{
		while (dir != NULL)
		{
			cmd_path = malloc(strlen(dir) + strlen(command) + 2);
			if (cmd_path == NULL)
			{
				perror("find_command");
				exit(EXIT_FAILURE);
			}

			sprintf(cmd_path, "%s/%s", dir, command);
			if (access(cmd_path, X_OK) == 0)
			{
				break;
			}

			free(cmd_path);
			cmd_path = NULL;
			dir = strtok(NULL, ":");
		}

		free(path_dirs);
	}

	return (cmd_path);
}
