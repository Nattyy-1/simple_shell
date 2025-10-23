#include "main.h"

/**
 * handle_builtin - handles shell builtin commands
 * @command: the shell builtin command that is executed
 * @last_exit_code: the exit code of the last executed command
 * @command_arguments: the list of arguments passed with the command
 * @shell_name: the name of the shell
 */
void handle_builtin(char *command, int last_exit_code, char **command_arguments, char *shell_name)
{
	if (_strcmp(command, "exit") == 0)
		exit_shell(last_exit_code, command_arguments, shell_name);
	else if (_strcmp(command, "env") == 0)
		print_env();
	else if (_strcmp(command, "setenv") == 0)
		set_env(command_arguments);
	else if (_strcmp(command, "unsetenv") == 0)
		unset_env(command_arguments);
}
