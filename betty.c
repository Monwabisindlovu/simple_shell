#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define main my_main

/**
 * my_main - Entry point
 *
 * Return: Always 0 (Success)
 */
int my_main(void)
{
int fd;

fd = open("holberton", O_CREAT | O_WRONLY | O_TRUNC, 0600);
if (fd == -1)
return (1);

write(fd, "Holberton School!\n", 17);
close(fd);

return (0);
}

