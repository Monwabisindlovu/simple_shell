#include "shell.h"

/**
 * add_node_start - adds a node to the beginning of the linked list
 * @list: address of pointer to head node
 * @data: data field of the node
 * @index: index associated with the node
 *
 * Return: size of the linked list
 */
list_t *add_node_start(list_t **list, const char *data, int index)
{
	list_t *new_node;

	if (!list)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *list;
	*list = new_node;
	return (new_node);
}

/**
 * add_node_end - adds a node to the end of the linked list
 * @list: address of pointer to head node
 * @data: data field of the node
 * @index: index associated with the node
 *
 * Return: size of the linked list
 */
list_t *add_node_end(list_t **list, const char *data, int index)
{
	list_t *new_node, *node;

	if (!list)
		return (NULL);

	node = *list;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*list = new_node;
	return (new_node);
}

/**
 * print_list_data - prints only the data element of a linked list
 * @head: pointer to the first node
 *
 * Return: size of the linked list
 */
size_t print_list_data(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->data ? head->data : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_index - deletes a node at the given index
 * @list: address of pointer to head node
 * @index: index of the node to delete
 *
 * Return: (1) on success, (0) on failure
 */
int delete_node_at_index(list_t **list, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int count = 0;

	if (!list || !*list)
		return (0);

	if (!index)
	{
		node = *list;
		*list = (*list)->next;
		free(node->data);
		free(node);
		return (1);
	}
	node = *list;
	while (node)
	{
		if (count == index)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}
		count++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a linked list
 * @list_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **list_ptr)
{
	list_t *node, *next_node, *head;

	if (!list_ptr || !*list_ptr)
		return;
	head = *list_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}
	*list_ptr = NULL;
}

