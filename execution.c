#include "shell.h"

/**
 * print_prompt - Displays the shell prompt.
 *
 * Description:
 * This function prints the shell prompt, which is typically
 * displayed to indicate that the shell is ready to accept user input.
 * The prompt is usually a symbol (e.g., "$") followed by a space.
 */
void print_prompt(void)
{
    const char msg[] = "$ ";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

/**
 * execute_external_command - Execute an external command.
 * @command_path: Path to the executable command.
 * @args: Array of command arguments.
 *
 * Description:
 * Executes an external command using the fork and execve system
 * calls. It creates a child process to execute the command and waits
 * for the child process to complete. The function handles errors that
 * may arise during process creation and completion.
 */
void execute_external_command(char *command_path, char **args)
{
	pid_t child_pid, wait_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return;
	}

	if (child_pid == 0)
	{
		execve(command_path, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait_pid = waitpid(child_pid, &status, 0);
		if (wait_pid == -1)
		{
			perror("waitpid");
		}
	}
}

/**
 * execute_command - Execute the given command.
 * @args: Array of command arguments.
 *
 * Description:
 * Executes the provided command by calling the appropriate function
 * based on whether it's a built-in command or an external command.
 */
void execute_command(char **args)
{
	if (is_builtin_command(args[0]))
	{
		if (strcmp(args[0], "exit") == 0)
		{
			builtin_exit(args);
		}
	}
	else
	{
		find_and_execute_command(args);
	}
}
