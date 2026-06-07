#include "main.h"

/**
 * update_env_var - updates an existing environment variable in place
 * @var_name: the variable name to look for
 * @value: the new value to assign
 *
 * Assumes environ is already shell-owned (see own_environ), since it may
 * free and replace an existing entry.
 *
 * Return: 1 if the variable already existed (updated or unchanged),
 *         0 if it was not found
 */
int update_env_var(char *var_name, char *value)
{
	int i = 0;
	char *env, *env_name, *env_value;

	while (environ[i] != NULL)
	{
		env = strdup(environ[i]);
		env_name = _strtok(env, "=");
		env_value = env + _strlen(env_name) + 1;

		if (_strcmp(env_name, var_name) == 0 && _strcmp(env_value, value) == 0)
		{
			free(env);
			return (1);
		}
		if (_strcmp(env_name, var_name) == 0)
		{
			free(environ[i]);
			environ[i] = concatenate_env(var_name, value);
			free(env);
			return (1);
		}
		free(env);
		i++;
	}
	return (0);
}

/**
 * append_env_var - adds a new variable to the environment
 * @var_name: the variable name
 * @value: the variable value
 *
 * Assumes environ is already shell-owned (see own_environ), since it frees
 * the old environ array.
 */
void append_env_var(char *var_name, char *value)
{
	int i, count = 0;
	char **new_environ;

	while (environ[count] != NULL)
		count++;

	new_environ = malloc(sizeof(char *) * (count + 2));
	if (!new_environ)
		return;

	for (i = 0; i < count; i++)
		new_environ[i] = environ[i];

	new_environ[count] = concatenate_env(var_name, value);
	new_environ[count + 1] = NULL;

	free(environ);
	environ = new_environ;
}

/**
 * set_env - sets or updates an environment variable
 * @command_arguments: the arguments: setenv VARIABLE VALUE
 */
void set_env(char **command_arguments)
{
	if (command_arguments[0] && !command_arguments[1])
		print_env();
	else if (command_arguments[1] && !command_arguments[2])
		write(2, "setenv: Too few arguments\n", 26);
	else if (command_arguments[2] && !command_arguments[3])
	{
		if (own_environ() == -1)
			return;
		if (!update_env_var(command_arguments[1], command_arguments[2]))
			append_env_var(command_arguments[1], command_arguments[2]);
	}
	else
		write(2, "setenv: Too many arguments\n", 27);
}
