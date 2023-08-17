#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


#define BUFFER_SIZE 1024

int print_hello(void);
void print_prompt(void);
char *read_line(void);
char **lsh_split_line(char *line);
int lsh_cd(char **args);
int lsh_clear(void);


#endif /* SHELL_H */

