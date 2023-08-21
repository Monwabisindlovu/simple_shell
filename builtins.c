#include "shell.h"

/**
 * is_builtin_command - checks if the command is builtin command.
 * @command_name: Name of the command to check.
 *
 * Description:
 * This function determines whether the given command is a built-in
 * command or not and returns 1 if it is a builtin command, 0 otherwise
 *
 * Returns:
 *  - (1) if the command is a built-in command.
 *  - (0) if the command is not a built-in command.
 */
int is_builtin_command(const char *command_name)
{
	if (strcmp(command_name, "exit") == 0)
		return (1);
	return (0);
}

/**
 * builtin_exit - Exit the shell.
 * @args: Array of command arguments.
 * Return: 0 (always successful).
 *
 * Description:
 * This function implements the built-in command 'exit',
 * which exits the shell.
 */
int builtin_exit(char **args)
{
	(void) args;
	exit(0);
}
