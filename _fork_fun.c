#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * _fork_fun - Execute a command using fork and execve.
 * @arg: Command and its arguments.
 * @av: Array of arguments.
 * @env: Array of environment variables.
 * @lineptr: Original command line input.
 * @np: Path value.
 * @c: Flag indicating if the command is executable in PATH.
 * Return: Exit status of the command.
 */
int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c)
{
pid_t child_pid;
int status = 0;

child_pid = fork();
if (child_pid == -1)
{
perror("fork");
return (1);
}
if (child_pid == 0)
{
if (c == 0)
{
fprintf(stderr, "%s: %d: %s: not found\n", av[0], np, arg[0]);
free(lineptr);
free(arg);
exit(127);
}
if (execve(arg[0], arg, env) == -1)
{
perror("execve");
free(lineptr);
free(arg);
exit(126);
}
}
else
{
waitpid(child_pid, &status, 0);
}

return (status);
}

