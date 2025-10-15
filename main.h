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
int get_command(char **line, char **command);
int execute_command(char **command, char ***command_arguments);

#endif
