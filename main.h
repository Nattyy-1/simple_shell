#ifndef MAIN_H
#define MAIN_H

#define BUF_SIZE 1024

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

extern char **environ;
extern char **_environ;

int print_prompt(char **line, size_t *len);
int get_command(char **line, char **command, char ***command_arguments);
int execute_command(char **command, char ***command_arguments);
int _count_words(char *str);
int check_path(char **command);
int _strlen(char *str);
int is_builtin(char *command);
int _strcmp(char *str1, char *str2);
int _is_number(char *str);
char *concatenate_path(char *absolute_path, char *command);
char *concatenate_env(char *env_name, char *env_value);
char *_strtok(char *str, const char *delim);
char **get_substrings(char *line);
void handle_builtin(char *command, int last_exit_code, char **command_arguments, char *shell_name);
void print_env(void);
void exit_shell(int last_exit_code, char **command_arguments, char *shell_name);
void set_env(char **command_arguments);
void unset_env(char **command_arguments);
void cd(char **command_arguments, char *shell_name);
void handle_comment(char **line);

#endif
