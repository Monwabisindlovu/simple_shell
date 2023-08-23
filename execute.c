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
	pid_t pid;

	if (args[0] == NULL)
	{
		return (1);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		exit(0);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror("execute");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}

	return (1);
}
