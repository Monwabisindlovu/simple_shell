#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int print_hello(void);
int factorial(int n);
int main(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **tokenize_input(char *input);
int execute_command(char **args);
void free_tokens(char **tokens);
char *_getenv(char **env);
int _values_path(char **arg, char **env);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_get_path(char **env);
char *_getline_command(void);
char **tokenize(char *lineptr);
int _fork_fun(char **arg, char **av, char **env, char *lineptr, int np, int c);

#endif /* SHELL_H */

