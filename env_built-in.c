#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * shell_env - Print environment variables.
 *
 * Return: Always returns 1 to continue shell loop.
 */
int shell_env(void)
{
char **env = environ;

while (*env)
{
write(STDOUT_FILENO, *env, strlen(*env));
write(STDOUT_FILENO, "\n", 1);
env++;
}

return (1);
}

