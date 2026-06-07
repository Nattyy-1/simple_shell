#include "main.h"

/**
 * free_command - frees a command and its argument vector
 * @command: the command string to free
 * @command_arguments: the NULL-terminated argument vector to free
 */
void free_command(char *command, char **command_arguments)
{
	int j;

	if (command_arguments)
	{
		for (j = 0; command_arguments[j] != NULL; j++)
			free(command_arguments[j]);
		free(command_arguments);
	}
	free(command);
}
