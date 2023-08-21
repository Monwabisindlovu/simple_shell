#include "shell.h"

/**
 * construct_command_path - Construct the full path to a command.
 * @dir: Directory from PATH environment variable.
 * @command_name: Name of the command.
 * Return: A allocated string with the full command path.
 *
 * Description:
 * Constructs the full path to the command by combining the directory
 * from the PATH environment variable and the command name.
 */
char *construct_command_path(const char *dir, const char *command_name)
{
	size_t path_len = strlen(dir) + strlen(command_name) + 2;
	char *command_path = (char *) malloc(path_len);

	if (command_path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	snprintf(command_path, path_len, "%s/%s", dir, command_name);
	return (command_path);
}

/**
 * execute_command_path - Execute a command using its full path.
 * @args: Array of command arguments.
 * @command_path: Full path to the executable command.
 *
 * Description:
 * Executes a command using the fork and execve system calls. It creates
 * a child process to execute the command and waits for the child process
 * to complete. The function handles errors that may arise during process
 * creation and completion.
 */
void execute_command_path(char **args, const char *command_path)
{
	struct stat st;

	if (stat(command_path, &st) == 0 && st.st_mode & S_IXUSR)
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			free((void *)command_path);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execve(command_path, args, NULL);
			perror("execve");
			free((void *)command_path);
			_exit(EXIT_FAILURE);
		}
		else
		{
			int status;

			waitpid(pid, &status, 0);
			free((void *)command_path);
			return;
		}
	}

	free((void *)command_path);
}

/**
 * find_and_execute_command - Find and execute a command.
 * @args: Array of command arguments.
 *
 * Description:
 * Searches for the provided command in the PATH environment variable
 * and executes it if found. Displays an error message if the command
 * is not found.
 */
void find_and_execute_command(char **args)
{
	char *command_name = args[0];
	char *path = getenv("PATH");

	char *token = strtok(path, ":");

	while (token != NULL)
	{
		char *command_path = construct_command_path(token, command_name);

		execute_command_path(args, command_path);
		token = strtok(NULL, ":");
	}

	fprintf(stderr, "Command '%s' not found\n", command_name);
}
