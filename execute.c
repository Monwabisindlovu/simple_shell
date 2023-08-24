#include "shell.h"

/**
 * is_executable_cmd - Determines if a file is an executable command or not.
 * @info: Info structure
 * @path: Path to the file
 *
 * Return: (1) if true, (0) otherwise
 */
int is_executable_cmd(info_t *info, char *path)
{
	struct stat st;

	(void) info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * duplicate_characters - Duplicates characters within a range.
 * @path_str: The PATH to the string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: Pointer to the new buffer.
 */
char *duplicate_characters(char *path_str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			buf[k++] = path_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_cmd_in_path - Finds a command in the PATH string
 * @info: Info structure
 * @path_str: The PATH to the string
 * @cmd: The command to find it.
 *
 * Return: Full path of cmd if found, or (NULL)
 */
char *find_cmd_in_path(info_t *info, char *path_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_executable_cmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = duplicate_characters(path_str, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			if (is_executable_cmd(info, path))
				return (path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}

		i++;
	}

	return (NULL);
}
