#include "shell.h"

/**
 * handle_exit - Handle the exit command
 *
 * @args: An array of pointers to command and arguments.
 */
void handle_exit(char **args)
{
int status = 0;
if (args[1] != NULL)
{
status = atoi(args[1]);
if (status < 0)
{
char *error_msg = "exit: Illegal number: ";
write(STDERR_FILENO, error_msg, strlen(error_msg));
write(STDERR_FILENO, args[1], strlen(args[1]));
write(STDERR_FILENO, "\n", 1);
return;
}
}
exit(status);
}

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
char *line;
char **args;
int status;
do {
if (isatty(STDIN_FILENO))
{
write(STDOUT_FILENO, "$ ", 2);
}
line = read_line();
if (line == NULL)
{
break;
}
args = split_line(line);
if (strcmp(args[0], "exit") == 0)
{
handle_exit(args);
free(line);
free(args);
continue;
}
else if (strcmp(args[0], "cd") == 0)
{
cd_builtin(args);
free(line);
free(args);
continue;
}
else if (strcmp(args[0], "env") == 0)
{
write_env();
free(line);
free(args);
continue;
}
status = execute(args);
free(line);
free(args);
} while (status);
return (0);
}

