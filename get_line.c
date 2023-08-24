#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

/**
 * read_from_buffer - Read characters from the buffer into the output line
 * @lineptr: pointer to the input line
 * @n: size of the input line
 * @buffer: input buffer
 * @p: current position in the buffer
 * @available: number of available characters in the buffer
 *
 * Return: number of characters read from the buffer
 */
size_t read_from_buffer(char **lineptr, size_t *n, char *buffer,
char **p, size_t *available)
{
size_t total = 0;

(void) buffer;

while (*available > 0)
{
if (total + 1 >= *n)
{
*n *= 2;
*lineptr = realloc(*lineptr, *n);
if (*lineptr == NULL)
return (-1);
}
(*lineptr)[total++] = *(*p)++;
(*available)--;
if ((*lineptr)[total - 1] == '\n')
break;
}

return (total);
}

/**
 * _getline - custom getline function
 * @lineptr: pointer to the input line
 * @n: size of the input line
 * @stream: input stream
 *
 * Return: number of characters read, or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
static char buffer[BUFFER_SIZE];
static char *p;
static size_t available;
size_t total = 0;
ssize_t nread;

if (lineptr == NULL || n == NULL || stream == NULL)
{
errno = EINVAL;
return (-1);
}
if (*lineptr == NULL)
{
*n = BUFFER_SIZE;
*lineptr = malloc(*n);
if (*lineptr == NULL)
return (-1);
}
while (1)
{
if (available == 0)
{
nread = read(fileno(stream), buffer, BUFFER_SIZE);
if (nread <= 0)
break;
p = buffer;
available = nread;
}
total += read_from_buffer(lineptr, n, buffer, &p, &available);
if ((*lineptr)[total - 1] == '\n')
break;
if (total + BUFFER_SIZE >= *n) /* Check if the buffer is full */
{
*n += BUFFER_SIZE; /* Increase the buffer size */
*lineptr = realloc(*lineptr, *n); /* Reallocate memory for the input line */
if (*lineptr == NULL) /* If memory allocation fails */
return (-1); /* Return -1 to indicate failure */
}
}
if (nread == -1 || (nread == 0 && total == 0))
return (-1);
(*lineptr)[total] = '\0';
return (total);
}

