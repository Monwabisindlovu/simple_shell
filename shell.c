#include "shell.h"

/**
<<<<<<< HEAD
 * main - entry point of the simple shell program.
 * @ac: arg count
 * @av: arg vector
 *
 * Return: (0) on success, (1) on error.
=======
 * main - Entry point
 *
 * Return: Always 0
>>>>>>> 2ae2b796315b789e045bde6385055475f2aa2a32
 */
int main(int ac, char **av)
{
<<<<<<< HEAD
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
=======
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
free(line);
free(args);
exit(0);
}
status = execute(args);

free(line);
free(args);
} while (status);

return (0);
>>>>>>> 2ae2b796315b789e045bde6385055475f2aa2a32
}
