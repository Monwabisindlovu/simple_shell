#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define INITIAL_BUFSIZE 64

/* Function declarations */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int _isblank(char *str);
int exit_shell(char **args);
int print_env(char **args);
int change_dir(char **args);
extern char **environ;
int print_env(char **args);
int change_dir(char **args);
#endif

