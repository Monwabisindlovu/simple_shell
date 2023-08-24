#include "shell.h"

/**
 * display_history - Displays the list of the history,
 * one command per line, preceded by line numbers starting at 0.
 * @info: Parameter struct containing potential arguments.
 *
 * Return: Always (0)
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_user_alias - removes an alias from the alias list
 * @info: Parameter struct.
 * @alias_str: The string representing the alias.
 *
 * Return: Always (0) on success, 1 when error.
 */
int unset_user_alias(info_t *info, char *alias_str)
{
	char *equal_sign, temp_char;
	int result;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);
	temp_char = *equal_sign;
	*equal_sign = '\0';
	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
	*equal_sign = temp_char;
	return (result);
}

/**
 * set_user_alias - sets an alias in the alias list.
 * @info: Parameter struct.
 * @alias_str: The string representing the alias.
 *
 * Return: Always (0) on success, (1) when error.
 */
int set_user_alias(info_t *info, char *alias_str)
{
	char *equal_sign, *value;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);
	value = equal_sign + 1;
	if (!*value)
		return (unset_user_alias(info, alias_str));

	unset_user_alias(info, alias_str);
	return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_user_alias - prints an alias string.
 * @node: Is alias node
 *
 * Return: Always (0) on success, (1) when error.
 */
int print_user_alias(list_t *node)
{
	char *equal_sign, *alias_value;

	if (node)
	{
		equal_sign = _strchr(node->str, '=');
		if (equal_sign)
		{
			alias_value = equal_sign + 1;
			for (char *ch = node->str; ch <= equal_sign; ch++)
				_putchar(*ch);
			_putchar('\'');
			_puts(alias_value);
			_puts("'\n");
			return (0);
		}
	}

	return (1);
}

/**
 * manage_alias - mimics the alias builtin (man alias).
 * @info: Parameter struct.
 *
 * Return: Always (0)
 */
int manage_alias(info_t *info)
{
	int i = 0;
	char *equal_sign, *alias_value;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_user_alias(node);
			node = node->next;
		}

		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign = _strchr(info->argv[i], '=');
		if (equal_sign)
			set_user_alias(info, info->argv[i]);
		else
			print_user_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
