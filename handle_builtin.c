#include "main.h"

/**
 * handle_builtin - handles shell builtin commands
 * @command: the shell builtin command that is executed
 * @last_exit_code: the exit code of the last executed command
 */
void handle_builtin(char *command, int last_exit_code)
{
	if (_strcmp(command, "exit") == 0)
		exit(last_exit_code);
	else if (_strcmp(command, "env") == 0)
		print_env();
}
