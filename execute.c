#include <sys/stat.h>
#include <unistd.h>
#include "shell.h"

/**
 * execute - executes a command with arguments
 * @args: an array of pointers to command and arguments
 *
 * Return: 1 if the shell should continue running, 0 if it should exit
 */
int execute(char **args)
{
    pid_t pid;
    int status;
    char *builtin[] = {"exit", "env", "cd", NULL};
    int (*func[])(char **) = {&exit_shell, &print_env, &change_dir};
    int i;
    char *path, *path_value, *cmd_path;
    char *token, *saveptr;
    struct stat st;

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

    path = getenv("PATH");
    path_value = strdup(path);
    token = strtok_r(path_value, ":", &saveptr);
    while (token != NULL)
    {
        cmd_path = malloc(strlen(token) + strlen(args[0]) + 2);
        sprintf(cmd_path, "%s/%s", token, args[0]);
        if (stat(cmd_path, &st) == 0)
        {
            args[0] = cmd_path;
            break;
        }
        free(cmd_path);
        token = strtok_r(NULL, ":", &saveptr);
    }
    free(path_value);

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

