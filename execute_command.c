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
	*command_arguments = malloc(sizeof(char *) * 2);

	if (*command_arguments == NULL)
	{
		perror("malloc");
		return (-1);
	}

	(*command_arguments)[0] = *command;
	(*command_arguments)[1] = NULL;

	if (execve(*command, *command_arguments, environ) == -1)
	{
		perror(*command);
		free(*command_arguments);
		return (-1);
	}

	return (0);
}
