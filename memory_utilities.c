#include "shell.h"

/**
 * set_memory - fills memory with a given byte value.
 * @dest: the pointer to the memory area
 * @value: the byte value to fill *dest with
 * @n: the number of bytes to fill
 *
 * Return: (dest) a pointer to the memory area dest
 */
char *set_memory(char *dest, char value, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = value;
	return (dest);
}

/**
 * free_strings - frees an array of strings
 * @string_array: array of strings
 */
void free_strings(char **string_array)
{
	char **temp = string_array;

	if (!string_array)
		return;
	while (*string_array)
		free(*string_array++);
	free(temp);
}

/**
 * resize_memory - reallocates a block of memory
 * @ptr: pointer to previous allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated memory block
 */
void *resize_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
