#include "shell.h"

/**
 * fetch_environ_copy - Returns a copy of the environment string array
 * @info: Structure with arguments. Maintains function prototype.
 * Return: Pointer to the environment string array
 */
char **fetch_environ_copy(info_t *info)
{
	if (!info->env_vars || info->env_changed)
	{
		info->env_vars = list_to_strings(info->env_list);
		info->env_changed = 0;
	}

	return (info->env_vars);
}

/**
 *unset_env_var - Remove an environment variable
 *@info: Structure with arguments. Maintains function prototype.
 *Return: 1 on delete, 0 otherwise
 *@var: The environment variable to remove
 */
int unset_env_var(info_t *info, char *var)
{
	list_t *node = info->env_list;
	size_t index = 0;
	char *p;

	if (!node || !var)
	{
		return (0);
	}

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env_list), index);
			index = 0;
			node = info->env_list;
			continue;
		}

		node = node->next;
		index++;
	}

	return (info->env_changed);
}

/**
 * set_env_var - Initialize/modify a new/existing environment variable.
 * @info: Structure with arguments. Maintains function prototype.
 * @var: The environment variable to set or modify
 * @value: The value of the environment variable
 *
 * Return: Always (0)
 */
int set_env_var(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
	{
		return (0);
	}

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
	{
		return (1);
	}

	_strcpy(buf,
		var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env_list;

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}

		node = node->next;
	}

	add_node_end(&(info->env_list), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
