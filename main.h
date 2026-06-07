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

int print_prompt(char **line, size_t *len);
int get_command(char **line, char **command, char ***command_arguments);
char **build_arguments(char *command, int argument_count);
int execute_command(char **command, char ***command_arguments);
int run_command(char *sub_string, char *shell_name, int last_exit_code);
int _count_words(char *str);
int check_path(char **command);
char *search_path(char *path_copy, char *command);
int own_environ(void);
int _strlen(char *str);
int is_builtin(char *command);
int _strcmp(char *str1, char *str2);
int _is_number(char *str);
char *concatenate_path(char *absolute_path, char *command);
char *concatenate_env(char *env_name, char *env_value);
char *_strtok(char *str, const char *delim);
int is_delim(char c, const char *delim);
char **get_substrings(char *line);
int count_commands(char *line);
void handle_builtin(char *command, int last_exit_code,
		char **command_arguments, char *shell_name);
void print_env(void);
void exit_shell(int last_exit_code, char **command_arguments,
		char *shell_name);
void set_env(char **command_arguments);
int update_env_var(char *var_name, char *value);
void append_env_var(char *var_name, char *value);
void unset_env(char **command_arguments);
int find_env_index(char *name);
void remove_env_at(int index);
void cd(char **command_arguments, char *shell_name);
void cd_error(char *shell_name, char *path);
void cd_home(char *shell_name);
void cd_previous(char *old_wd, char *shell_name);
void handle_comment(char **line);
void free_command(char *command, char **command_arguments);

#endif
