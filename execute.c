#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"

/**
 * execute - Execute a command with arguments.
 *
 * @args: An array of pointers to command and arguments.
 * Return: 1 if the shell should continue running, 0
 * if the shell should exit.
 */
int execute(char **args)
{
	char *cmd_path = find_command(args[0]);
	pid_t pid;
        int status;

	if (args[0] == NULL)
	{
		return (1);
	}
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		return (0);
	}
	if (cmd_path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, NULL) == -1)
		{
			perror("execute");
		}

		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("execute");
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	free(cmd_path);
	return (1);
}
