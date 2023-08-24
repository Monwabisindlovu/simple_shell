#include "shell.h"

/**
 * ischain - checks if current char in buffer is a chain delimiter
 * @info: the parameter structure
 * @buf: the character buffer
 * @p: address of current position in buf
 *
 * Return: (1) if chain delimiter, (0) otherwise
 */
int ischain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Checks if we should continue chaining based on last status
 * @info: IS the parameter structure.
 * @buf: Is the character buffer
 * @p: THE address of current position in buf.
 * @i: THE starting position in buf
 * @len: length of buf.
 *
 *Return: (Void)
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces aliases that are in the tokenized string
 * @info: Is The parameter structure
 *
 * Return: (1) if replaced, (0) otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}

	return (1);
}

/**
 * replace_vars - replaces the variables in the tokenized string
 * @info: Is the parameter structure
 *
 * Return: (1) if replaced, (0) otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_str(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
			continue;
		}

		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_str(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}

		node = find_node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_str(&(info->argv[i]), _strdup(strchr(node->str, '=') + 1));
			continue;
		}

		replace_str(&info->argv[i], _strdup(""));
	}

	return (0);
}

/**
 * replace_string - replaces the  string.
 * @old: Is The address of old string
 * @new: New string being used
 *
 * Return: (1) if replaced, (0) otherwise
 */
int replace_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
