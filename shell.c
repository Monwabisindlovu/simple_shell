#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024

/**
 * print_prompt - Displays the shell prompt.
 */
void print_prompt(void)
{
const char msg[] = "$ ";
write(STDOUT_FILENO, msg, sizeof(msg)-1);
}

/**
 * read_line - Reads a line of input from the user.
 *
 * Return: A pointer to the input line.
 */
char *read_line(void)
{
char *line = NULL;
size_t buffsize = 0;
ssize_t chars_read;

chars_read = getline(&line, &buffsize, stdin);

if (chars_read == -1)
{
if (feof(stdin))
{
write(STDOUT_FILENO, "\n", 1);
free(line);
return (NULL);
}
else
{
perror("read_line");
exit(EXIT_FAILURE);
}
}
return (line);
}

/**
 * execute_command - Execute the given command.
 * @command: The command to execute.
 *
 * Description:
 * Executes the provided command using the fork and execve system
 * calls. It creates a child process to execute the command and waits
 * for the child process to complete. The function handles errors that
 * may arise during process creation and completion .
 */
void execute_command(char **args)
{
pid_t child_pid, wait_pid;
int status;

child_pid = fork();

if (child_pid == -1)
{
perror("fork");
return;
}

if (child_pid == 0)
{
execve(args[0], args, NULL);
perror("execve");
exit(EXIT_FAILURE);
}
else
{
wait_pid = waitpid(child_pid, &status, 0);
if (wait_pid == -1)
{
perror("waitpid");
}
}
}
/**
 * main - Entry point of the command-line interpreter.
 *
 * This function implements a simple interactive shell-like
 * loop where it continuously
 * prompts the user for input, reads the provided command line,
 * tokenizes it into arguments,
 * and then executes the corresponding command.
 * The loop repeats indefinitely until the user
 * chooses to exit the shell.
 *
 * Return: Always returns 0 to indicate successful program execution.
 */
int main(void)
{
char *line;
char **args;
int i;

while (1)
{
print_prompt();
line = read_line();

if (!line)
break;

if (strlen(line) > 0)
{
args = malloc(MAX_INPUT_SIZE * sizeof(char *));
i = 0;
args[i] = strtok(line, " \n");

while (args[i] != NULL)
{
i++;
args[i] = strtok(NULL, " \n");
}
args[i] = NULL;

execute_command(args);

free(args);
}

free(line);
}

return (0);
}

