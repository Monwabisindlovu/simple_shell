#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

/**
 * change_dir - Change the current working directory.
 *
 * @args: An array of pointers to command and arguments.
 * Return: 1 if success, 0 otherwise.
 */
int change_dir(char **args)
{
char *dir;
char *oldpwd;
char *pwd;
int ret;

if (args[1] == NULL || strcmp(args[1], "~") == 0)
{
dir = getenv("HOME");
}
else if (strcmp(args[1], "-") == 0)
{
dir = getenv("OLDPWD");
}
else
{
dir = args[1];
}
oldpwd = getcwd(NULL, 0);
ret = chdir(dir);
if (ret == -1)
{
perror("change_dir");
free(oldpwd);
return (1);
}
pwd = getcwd(NULL, 0);
setenv("OLDPWD", oldpwd, 1);
setenv("PWD", pwd, 1);
free(oldpwd);
free(pwd);
return (1);
}

/**
 * print_env - Print the current environment variables.
 *
 * @args: An array of pointers to command and arguments.
 * Return: 1 if success, 0 otherwise.
 */
int print_env(char **args __attribute__((unused)))
{
extern char **environ;
int i;

for (i = 0; environ[i] != NULL; i++)
{
printf("%s\n", environ[i]);
}

return (1);
}

/**
 * exit_shell - Exit the shell.
 *
 * @args: An array of pointers to command and arguments.
 * Return: 0 to indicate exit.
 */
int exit_shell(char **args __attribute__((unused)))
{
return (0);
}

/**
 * execute_builtin - Execute a built-in command.
 *
 * @args: An array of pointers to command and arguments.
 * Return: 1 if the shell should continue running, 0
 * if the shell should exit, or -1 if the command is not a built-in.
 */
int execute_builtin(char **args)
{
char *builtins[] = {"cd", "env", "exit", NULL};
int (*functions[])(char **) = {change_dir, print_env, exit_shell};
int i;

if (args == NULL || args[0] == NULL)
{
return (-1);
}

for (i = 0; builtins[i] != NULL; i++)
{
if (strcmp(args[0], builtins[i]) == 0)
{
return (functions[i](args));
}
}

return (-1);
}

