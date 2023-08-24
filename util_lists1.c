#include "shell.h"

/**
 * get_list_length - calculates the length of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t get_list_length(const list_t *h)
{
	size_t length = 0;

	while (h)
	{
		h = h->next;
		length++;
	}
	return (length);
}

/**
 * list_to_string_array - converts a linked list of strings,
 * to an array of strings
 *
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_string_array(list_t *head)
{
	list_t *node = head;
	size_t length = get_list_length(head), i;
	char **string_array;
	char *string;

	if (!head || !length)
		return (NULL);
	string_array = malloc(sizeof(char *) * (length + 1));
	if (!string_array)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		string = malloc(_strlen(node->str) + 1);
		if (!string)
		{
			for (size_t j = 0; j < i; j++)
				free(string_array[j]);
			free(string_array);
			return (NULL);
		}

		string = _strcpy(string, node->str);
		string_array[i] = string;
	}
	string_array[i] = NULL;
	return (string_array);
}

/**
 * display_list - prints all elements of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t display_list(const list_t *h)
{
	size_t length = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		length++;
	}
	return (length);
}

/**
 * find_node_with_prefix - returns the node,
 * the string starts with a given prefix
 *
 * @node: pointer to the head of the list
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or (NULL)
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_position - gets the position of a node in the list
 * @head: pointer to the head of the list
 * @node: pointer to the node
 *
 * Return: position of the node or (-1)
 */
ssize_t get_node_position(list_t *head, list_t *node)
{
	size_t position = 0;

	while (head)
	{
		if (head == node)
			return (position);
		head = head->next;
		position++;
	}
	return (-1);
}
