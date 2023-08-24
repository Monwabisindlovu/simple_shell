#include "shell.h"

/**
 * get_histfile_path - retrieves the path to the history file
 * @info: parameter structure
 *
 * Return: allocated string containing the history file path
 */
char *get_histfile_path(info_t *info)
{
	char *path, *home_dir;

	home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return (NULL);
	path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!path)
		return (NULL);
	path[0] = 0;
	_strcpy(path, home_dir);
	_strcat(path, "/");
	_strcat(path, HIST_FILE);
	return (path);
}

/**
 * save_history - creates or appends to the history file
 * @info: parameter structure
 *
 * Return: (1) on success, (-1) on failure.
 */
int save_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_histfile_path(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history_list; node; node = node->next)
	{
		_puts_to_fd(node->str, fd);
		_putc_to_fd('\n', fd);
	}

	_putc_to_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * load_history - reads history entries from the file
 * @info: parameter structure
 *
 * Return: number of loaded entries on success, (0) on failure
 */
int load_history(info_t *info)
{
	int i, last = 0, entry_count = 0;
	ssize_t fd, rdlen, file_size = 0;
	struct stat st;
	char *buf = NULL, *filename = get_histfile_path(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (file_size + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, file_size);
	buf[file_size] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < file_size; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			add_history_entry(info, buf + last, entry_count++);
			last = i + 1;
		}

	if (last != i)
		add_history_entry(info, buf + last, entry_count++);
	free(buf);
	info->hist_entry_count = entry_count;
	while (info->hist_entry_count-- >= HIST_MAX)
		delete_node_at_index(&(info->history_list), 0);
	renumber_history_entries(info);
	return (info->hist_entry_count);
}

/**
 * add_history_entry - appends an entry to the history linked list
 * @info: parameter structure
 * @buf: buffer containing history entry
 * @entry_count: the history entry count
 *
 * Return: (0)
 */
int add_history_entry(info_t *info, char *buf, int entry_count)
{
	list_t *node = NULL;

	if (info->history_list)
		node = info->history_list;
	add_node_end(&node, buf, entry_count);

	if (!info->history_list)
		info->history_list = node;
	return (0);
}

/**
 * renumber_history_entries - renumbers the history linked list entries
 * @info: parameter structure
 *
 * Return: the updated hist_entry_count
 */
int renumber_history_entries(info_t *info)
{
	list_t *node = info->history_list;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->hist_entry_count = i);
}
