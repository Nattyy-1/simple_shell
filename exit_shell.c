#include "main.h"

/**
 * exit_shell - exits the shell
 * @last_exit_code: the default exit code if no arguments are passed
 * @command_arguments: the arguments to exit (custom exit status)
 * @shell_name: the name of the shell
 */
void exit_shell(int last_exit_code, char **command_arguments, char *shell_name)
{
	int exit_code;

	if (command_arguments == NULL || command_arguments[1] == NULL)
		exit(last_exit_code);
	else
	{
		exit_code = _is_number(command_arguments[1]);
		if (exit_code == -1)
		{
			write(1, shell_name, _strlen(shell_name));
			write(1, ": 1: exit: Illegal number : ", 28);
			write(1, command_arguments[1], _strlen(command_arguments[1]));
			write(1, "\n", 1);
		} else
			exit(exit_code);
	}
}
