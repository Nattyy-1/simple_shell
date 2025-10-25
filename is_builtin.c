#include "main.h"

/**
 * is_builtin - checks if a given command is a shell builtin
 * @command: the command to be checked
 *
 * Return: 1 if it is a shell builtin, otherwise 0
 */
int is_builtin(char *command)
{
	if (_strcmp(command, "exit") == 0 || _strcmp(command, "env") == 0 ||
	    _strcmp(command, "setenv") == 0 || _strcmp(command, "unsetenv") == 0
	    || _strcmp(command, "cd") == 0)
		return (1);

	return (0);
}
