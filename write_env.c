#include <unistd.h>
#include <string.h>
#include "shell.h"

/**
 * write_env - Print the current environment.
 *
 */
void write_env(void)
{
int i;
size_t len;

for (i = 0; environ[i] != NULL; i++)
{
len = strlen(environ[i]);
write(STDOUT_FILENO, environ[i], len);
write(STDOUT_FILENO, "\n", 1);
}
}

