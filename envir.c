#include "shell.h"
/**
 * print_env - Prints the current environment variables.
 * @info: Structure with arguments. Maintains function prototype.
 *
 * Return: Always (0).
 */
int print_env(info_t *info)
{
	print_str_list(info->env_vars);
	return (0);
}

/**
 * fetch_env - fetches the value of an environment variable.
 * @info: Structure with arguments. Maintains function prototype.
 * @name: Name of the env. variable.
 *
 * Return: the value of the env variable.
 */
char *fetch_env(info_t *info, const char *name)
{
	list_t *node = info->env_vars;
	char *val;

	while (node)
	{
		val = starts_with(node->str, name);
		if (val && *val)
			return (val);
		node = node->next;
	}

	return (NULL);
}

/**
 * set_env - Initialize or modify an environment variable.
 * @info: Structure with arguments. Maintains function prototype.
 * Return: Always (0)
 */
int set_env(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env - Remove/deletes an environment variable.
 * @info: Structure with arguments. Maintains function prototype.
 *
 * Return: Always (0).
 */
int unset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list.
 * @info: Structure with arguments. Maintains function prototype.
 *
 * Return: Always (0)
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
