#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

/**
 * find_executable - Find an executable file in the PATH directories.
 *
 * @command: The command to be executed.
 * Return: A pointer to the full path of the executable file,
 * or NULL if not found or an error occurs.
 */
char *find_executable(char *command)
{
char *path;
char **dirs;
char *executable;
int i;

if (command == NULL || command[0] == '\0')
{
return (NULL);
}
if (access(command, X_OK) == 0)
{
return (strdup(command));
}
path = getenv("PATH");
if (path == NULL)
{
return (NULL);
}
dirs = split_line(path);
if (dirs == NULL)
{
return (NULL);
}
executable = NULL;
for (i = 0; dirs[i] != NULL; i++)
{
executable = malloc(strlen(dirs[i]) + strlen(command) + 2);
if (executable == NULL)
{
perror("find_executable");
break;
}
sprintf(executable, "%s/%s", dirs[i], command);
if (access(executable, X_OK) == 0)
{
break;
}
free(executable);
executable = NULL;
}
free(dirs);
return (executable);
}

