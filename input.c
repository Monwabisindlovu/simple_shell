#include "shell.h"

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
