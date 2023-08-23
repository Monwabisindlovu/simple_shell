#include "shell.h"

/**
 * execute_command - Execute a command using execve and handle child processes.
 * @cmd_path: The full path of the command to execute.
 * @args: An array of strings containing the command and its arguments.
 *
 * Return: The exit status of the executed command.
 */
int execute_command(char *cmd_path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("execute_command");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("execute_command");
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}

	return (status);
}

/**
 * execute - Execute a command with its arguments.
 *
 * @cmd_path: The full path of the command to execute.
 * @args: An array of strings containing the command and its arguments.
 *
 * Return: The exit status of the executed command.
 */
int execute(char *cmd_path, char **args)
{
	int status = execute_command(cmd_path, args);

	if (args[0] == NULL)
	{
		return (1);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		_exit(0);
	}

	if (cmd_path == NULL)
	{
		char error_message[] = "Command not found: ";

		write(STDERR_FILENO, error_message, strlen(error_message));
		write(STDERR_FILENO, args[0], strlen(args[0]));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}

	return (status);

}
