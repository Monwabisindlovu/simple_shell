#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"


/**
 * execute - Execute a command with arguments.
 *
 * @args: An array of pointers to command and arguments.
 * Return: 1 if the shell should continue running, 0
 * if the shell should exit.
 */
int execute(char **args)
{
pid_t pid;
int status;
char *builtin[] = {"exit", "env", "cd", NULL};
int (*func[])(char **) = {&exit_shell, &print_env, &change_dir};
int i;

if (args[0] == NULL)
{
return (1);
}

for (i = 0; builtin[i]; i++)
{
if (strcmp(args[0], builtin[i]) == 0)
{
return ((*func[i])(args));
}
}

pid = fork();
if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("execute");
}
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
perror("execute");
}
else
{
waitpid(pid, &status, WUNTRACED);
}

return (1);
}

/**
 * exit_shell - Exit the shell with a status code.
 *
 * @args: An array of pointers to command and arguments.
 * Return: 0 if success, 1 otherwise.
 */
int exit_shell(char **args)
{
int status;

if (args[1] == NULL)
{
status = 0;
}
else
{
status = atoi(args[1]);
if (status == -1)
{
fprintf(stderr, "exit: Illegal number: %s\n", args[1]);
return (1);
}
}
free(args);
exit(status);
}

/**
 * print_env - Print the environment variables.
 *
 * @args: An array of pointers to command and arguments.
 * Return: 1 if success, 0 otherwise.
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

