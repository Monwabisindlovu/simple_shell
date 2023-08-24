#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "shell.h"

/**
 * cd_builtin - Change the current directory.
 *
 * @args: An array of arguments.
 * Return: 0 on success, or 1 if an error occurs.
 */
int cd_builtin(char **args)
{
char *path;
char *oldpwd;
char *pwd;
char cwd[1024];

if (args[1] == NULL || strcmp(args[1], "~") == 0)
{
path = getenv("HOME");
}
else if (strcmp(args[1], "-") == 0)
{
path = getenv("OLDPWD");
if (path != NULL)
{
write(STDOUT_FILENO, path, strlen(path));
write(STDOUT_FILENO, "\n", 1);
}
}
else
{
path = args[1];
}

oldpwd = getcwd(cwd, sizeof(cwd));
if (chdir(path) != 0)
{
perror("cd");
return (1);
}
pwd = getcwd(cwd, sizeof(cwd));
setenv("OLDPWD", oldpwd, 1);
setenv("PWD", pwd, 1);

return (0);
}


