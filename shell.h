#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024

extern char **environ;

int print_hello(void);
void print_prompt(void);
char *read_line(void);
char **lsh_split_line(char *line);
void lsh_cd(char **args);
void lsh_clear(void);

/* execution.c */
void execute_command(char **args);

/* execution1.c code */
void find_and_execute_command(char **args);
char *construct_command_path(const char *dir, const char *command_name);
void execute_command_path(char **args, const char *command_path);

/* builtins.c code */
int is_builtin_command(const char *command_name);
int builtin_exit(char **args);

#endif
