#include "shell.h"

/**
 *read_line - Read a line of input from stdin.
 *
 *Return: A pointer to the input line (string),
 *or NULL if end-of-file is reached.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;
	ssize_t len;

	if ((len = getline(&line, &buffer_size, stdin)) == -1)
	{
		if (feof(stdin))
		{
			free(line);
			return (NULL);
		}
		else
		{
			perror("read_line");
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}

	return (line);
}
