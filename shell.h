#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 1024

extern char **environ;

/* Function declarations */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
void write_env(void);
void print_env(void);
int cd_builtin(char **args);
#endif
