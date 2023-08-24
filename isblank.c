#include "shell.h"
#include <ctype.h>

int _isblank(char *str)
{
    while (*str)
    {
        if (!isspace(*str))
            return (0);
        str++;
    }
    return (1);
}

