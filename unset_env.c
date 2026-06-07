#include "main.h"

/**
 * find_env_index - finds the index of a variable in environ
 * @name: the variable name to search for
 *
 * Return: the index of the variable, or -1 if not present
 */
int find_env_index(char *name)
{
	int j = 0;
	char *env, *env_name;

	while (environ[j] != NULL)
	{
		env = strdup(environ[j]);
		if (!env)
		{
			perror("strdup");
			return (-1);
		}
		env_name = _strtok(env, "=");
		if (_strcmp(name, env_name) == 0)
		{
			free(env);
			return (j);
		}
		free(env);
		j++;
	}
	return (-1);
}

/**
 * remove_env_at - removes the environ entry at a given index
 * @index: the index of the entry to remove
 *
 * Frees the removed string and the old array, then points environ at
 * a compacted heap copy. Assumes environ is already shell-owned.
 */
void remove_env_at(int index)
{
	int k, idx = 0, count = 0;
	char **new_environ, **old_environ;

	while (environ[count] != NULL)
		count++;

	new_environ = malloc(sizeof(char *) * count);
	if (!new_environ)
	{
		perror("malloc");
		return;
	}
	for (k = 0; k < count; k++)
	{
		if (k == index)
		{
			free(environ[k]);
			continue;
		}
		new_environ[idx++] = environ[k];
	}
	new_environ[idx] = NULL;
	old_environ = environ;
	environ = new_environ;
	free(old_environ);
}

/**
 * unset_env - removes one or more environment variables
 * @command_arguments: the arguments: unsetenv VARIABLE...
 */
void unset_env(char **command_arguments)
{
	int i = 1, index;

	if (command_arguments[0] && !command_arguments[1])
	{
		write(2, "unsetenv: Too few arguments\n", 28);
		return;
	}
	if (own_environ() == -1)
		return;

	while (command_arguments[i] != NULL)
	{
		index = find_env_index(command_arguments[i]);
		if (index != -1)
			remove_env_at(index);
		i++;
	}
}
