#include "main.h"

/**
 * execute_command - executes a given shell command
 * @command: the command to be executed
 * @command_arguments: the arguments to be executed with the command
 *
 * Return: -1 if there is an error, otherwise 0
 */
int execute_command(char **command, char ***command_arguments)
{
	if (execve(*command, *command_arguments, environ) == -1)
	{
		perror(*command);
		free(*command_arguments);
		return (-1);
	}

	return (0);
}
