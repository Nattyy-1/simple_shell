#include "main.h"

/**
 * search_path - searches PATH directories for an executable
 * @path_copy: a writable copy of the PATH variable (tokenized in place)
 * @command: the command name to look for
 *
 * Return: a heap-allocated absolute path, or NULL if not found
 */
char *search_path(char *path_copy, char *command)
{
	struct stat st;
	char *dir, *absolute_path;

	dir = _strtok(path_copy, ":");
	while (dir != NULL)
	{
		absolute_path = concatenate_path(dir, command);
		if (stat(absolute_path, &st) == 0)
			return (absolute_path);
		free(absolute_path);
		dir = _strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * check_path - resolves a command to an executable path via PATH
 * @command: the command being checked; on success it is freed and
 *           replaced with a heap-allocated absolute path
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

	absolute_path = search_path(path_copy, *command);
	free(path_copy);
	if (absolute_path == NULL)
		return (-1);

	free(*command);
	*command = absolute_path;
	return (0);
}
