#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t len_p = 0;

	if (!*len) /*if buffer is empty, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_SIGINT);
#if USE_GETLINE
		read_bytes = getline(buf, &len_p, stdin);
#else
			read_bytes = custom_getline(info, buf, &len_p);
#endif
		if (read_bytes > 0)
		{
			if ((*buf)[read_bytes - 1] == '\n')
			{
				(*buf)[read_bytes - 1] = '\0'; /*removes trailing newline */
				read_bytes--;
			}

			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{*len = read_bytes;
				info->command_buffer = buf;
			}
		}
	}

	return (read_bytes);
}

/**
 * fetch_input - fetches or gets a line without the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t fetch_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t read_bytes = 0;
	char **buf_p = &(info->arguments), *p;

	_putchar(BUF_FLUSH);
	read_bytes = buffer_input(info, &buf, &len);
	if (read_bytes == -1)	/*End_OF_File */
		return (-1);
	if (len)
	{
		j = i;	/*initialize new iterator to current buf position */
		p = buf + i;	/*fetches pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len)	/*iterate to semicolon or the end */
		{
			if (ischain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /*add 1 past nulled ';'' */
		if (i >= len)
		{
			i = len = 0; /*resets the length and position */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /*pass back pointer to the current command */
		return (custom_strlen(p)); /*returns the length of current command */
	}

	*buf_p = buf; /*else not a chain, pass back buffer from custom_getline() */
	return (read_bytes);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: read result
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t read_result = 0;

	if (*i)
		return (0);
	read_result = read(info->readfd, buf, READ_BUF_SIZE);
	if (read_result >= 0)
		*i = read_result;
	return (read_result);
}

/**
 * custom_getline - gets the next line of input from STDIN.
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: string length
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t read_result = 0, str_length = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		str_length = *length;
	if (i == len)
		i = len = 0;

	read_result = read_buffer(info, buf, &len);
	if (read_result == -1 || (read_result == 0 && len == 0))
		return (-1);

	c = custom_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = custom_realloc(p, str_length, str_length ? str_length + k : k + 1);
	if (!new_p)
		return (p ? (free(p), -1) : -1);

	if (str_length)
		custom_strncat(new_p, buf + i, k - i);
	else
		custom_strncpy(new_p, buf + i, k - i + 1);

	str_length += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = str_length;
	*ptr = p;
	return (str_length);
}

/**
 * handle_SIGINT - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void when program is done running
 */
void handle_SIGINT(__attribute__((unused)) int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
