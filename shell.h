#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 1024

/* Function declarations */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
extern char **environ;
int shell_exit(void);
#endif /* SHELL_H */
