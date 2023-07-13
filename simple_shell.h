#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* Header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>


extern char **environ;

void handle_signal(int sig);
void execute_command(char *command);
char *read_line(void);
char **split_line(char *line);
void free_args(char **args);

#endif

