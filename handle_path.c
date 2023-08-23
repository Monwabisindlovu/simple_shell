#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * get_path - Get the full path of a command.
 *
 * @command: The command to search for.
 * Return: The full path of the command if found, otherwise NULL.
 */
char *get_path(char *command)
{
char *path = getenv("PATH");
char *dir;
char *full_path = malloc(sizeof(char) * 1024);

while ((dir = strsep(&path, ":")) != NULL)
{
sprintf(full_path, "%s/%s", dir, command);
if (access(full_path, F_OK) == 0)
return (full_path);
}

free(full_path);
return (NULL);
}

