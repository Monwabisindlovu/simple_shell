#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/**
 * _values_path - Tokenize the PATH environment variable and check
 * if the command exists.
 * @command: The command to search for in the PATH directories.
 * @env: The environment variables array containing the PATH variable.
 * Return: (1) if the command exists in the PATH, (0) otherwise.
 */
int _values_path(char **command, char **env)
{
int i, len;
char *path, *dir, *path_copy;

for (i = 0; env[i] != NULL; i++)
{
if (strncmp(env[i], "PATH=", 5) == 0)
{
path = env[i] + 5;

path_copy = strdup(path);
if (!path_copy)
{
fprintf(stderr, "Memory allocation error\n");
return (0);
}

dir = strtok(path_copy, ":");
while (dir != NULL)
{
char *path_command;
len = strlen(dir) + 1 + strlen(*command);
path_command = (char *)malloc(len);
if (!path_command)
{
fprintf(stderr, "Memory allocation error\n");
free(path_copy);
return (0);
}

snprintf(path_command, len, "%s/%s", dir, *command);

if (access(path_command, X_OK) == 0)
{
free(*command);
*command = path_command;
free(path_copy);
return (1);
}

free(path_command);
dir = strtok(NULL, ":");
}

free(path_copy);
break;
}
}

return (0);
}

