#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * print_env - prints the current environment variables
 * @args: arguments passed to the function
 *
 * Return: 1 on success
 */
int print_env(char **args)
{
int i;

(void) args;
for (i = 0; environ[i]; i++)
{
write(STDOUT_FILENO, environ[i], strlen(environ[i]));
write(STDOUT_FILENO, "\n", 1);
}
return (1);
}

