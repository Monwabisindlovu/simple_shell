#include "shell.h"

/**
 * exit_shell - exits the shell
 * @args: arguments passed to the function
 *
 * Return: void
 */
int exit_shell(char **args)
{
free(args);
exit(0);
}

