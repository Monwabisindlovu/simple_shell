#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _getenv - Get the value of an environment variable.
 * @env: Array of environment variables.
 * Return: Pointer to the value of the variable, or NULL if not found.
 */
char *_getenv(char **env)
{

char *variable_name = "VARIABLE_NAME";

while (*env != NULL)
{
if (strncmp(*env, variable_name, strlen(variable_name)) == 0)
{
char *equals_sign = strchr(*env, '=');
if (equals_sign != NULL)
{
return (equals_sign + 1);
}
}
env++;
}

return (NULL);
}

