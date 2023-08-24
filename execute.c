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
int status;
char *executable;

pid = fork();
if (pid == 0)
{
executable = find_executable(args[0]);
if (executable == NULL)
{
fprintf(stderr, "%s: command not found\n", args[0]);
exit(EXIT_FAILURE);
}
if (execv(executable, args) == -1)
{
perror("execute");
}
free(executable);
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

return (1);
}

