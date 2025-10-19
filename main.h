#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern char **environ;

int print_prompt(char **line, size_t *len);
int get_command(char **line, char **command, char ***command_arguments);
int execute_command(char **command, char ***command_arguments);
int _count_words(char *str);
int check_path(char **command);
int _strlen(char *str);
int is_builtin(char *command);
int _strcmp(char *str1, char *str2);
char *concatenate_path(char *absolute_path, char *command);
void handle_builtin(char *command, int last_exit_code);
void print_env(void);

#endif
