#include <unistd.h>
#include "shell.h"

/**
 * change_dir - changes the current working directory
 * @args: arguments passed to the function
 *
 * Return: 1 on success
 */
int change_dir(char **args)
{
    char *dir;

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

    if (chdir(dir) != 0)
    {
        perror("change_dir");
    }

    return (1);
}

