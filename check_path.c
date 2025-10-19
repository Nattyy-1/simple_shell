#include "main.h"

/**
 * check_path - checks whether the command passed to the shell exists
 *		accross the system using the PATH environmental variable
 * @command: the command that is being checked
 *
 * Return: 0 if command is found, otherwise -1
 */
int check_path(char **command)
{
	struct stat st;
	char *path, *absolute_path, *path_copy;

	if (stat(*command, &st) == 0)
		return (0);

	path = getenv("PATH");
	if (!path)
		return (-1);

	path_copy = strdup(path);
	if (!path_copy)
		return (-1);

	absolute_path = _strtok(path_copy, ":");
	absolute_path = concatenate_path(absolute_path, *command);
	if (stat(absolute_path, &st) == 0)
	{
		*command = absolute_path;
		free(path_copy);
		return (0);
	}
	free(absolute_path);
	while (1)
	{
		absolute_path = _strtok(NULL, ":");
		if (absolute_path == NULL)
		{
			free(path_copy);
			return (-1);
		}
		absolute_path = concatenate_path(absolute_path, *command);
		if (stat(absolute_path, &st) == 0)
		{
			*command = absolute_path;
			free(path_copy);
			return (0);
		}
		free(absolute_path);
	}
}
