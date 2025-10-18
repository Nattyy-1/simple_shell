#include "main.h"

/**
 * concatenate_path - joins a directory path and a command with a slash
 * @dir: the absolute path (e.g. "/bin")
 * @command: the command (e.g. "ls")
 *
 * Return: pointer to newly allocated string containing full path, or NULL on
 *	   failure
 */
char *concatenate_path(char *dir, char *command)
{
	int i = 0, j = 0;
	int dir_len = 0, cmd_len = 0;
	char *full_path;

	dir_len = _strlen(dir);
	cmd_len = _strlen(command);

	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);

	for (i = 0; i < dir_len; i++)
		full_path[i] = dir[i];

	full_path[i++] = '/';

	for (j = 0; j < cmd_len; j++, i++)
		full_path[i] = command[j];

	full_path[i] = '\0';

	return (full_path);
}

