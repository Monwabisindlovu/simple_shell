#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_INPUT_BUFFSIZE 1024

extern char **environ;

#define TOKEN_DELIMITERS " \t\r\n\a"

char *read_line(void);
char **split_line(char *line);
char *get_path(char *command);
int execute(char *cmd_path, char **args);
int print_environment(void);
int shell_exit(void);

#endif
