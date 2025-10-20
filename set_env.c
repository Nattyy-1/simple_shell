#include "main.h"

/**
 * set_env - sets an environmental variable and its appropriate value
 * @command_arguments: the list of arguments passed with the command
 */
void set_env(char **command_arguments)
{
	int i = 0, found = 0, count = 0;
	char *var_name;
	char *value;
	char *env;
	char *env_name;
	char *env_value;
	char *temp;
	char **new_environ;

	if (command_arguments[0] && !command_arguments[1])
		print_env();
	else if (command_arguments[0] && command_arguments[1] && !command_arguments[2])
		write(2, "setenv: Too few arguments\n", 26);
	else if (command_arguments[0] && command_arguments[1] && command_arguments[2] &&
		!command_arguments[3])
	{
		var_name = command_arguments[1];
		value = command_arguments[2];

		while (environ[i] != NULL)
		{
			env = strdup(environ[i]);
			env_name = strtok(env, "=");
			env_value = env + _strlen(env_name) + 1;

			if (_strcmp(env_name, var_name) == 0 && _strcmp(env_value, value) == 0)
			{
				found = 1;
				free(env);
				break;
			}
			else if (_strcmp(env_name, var_name) == 0)
			{
				found = 1;
				temp = concatenate_env(var_name, value);
				free(environ[i]);
				environ[i] = temp;
				free(env);
				break;
			}
			free(env);
			i++;
		}

		if (!found)
		{
			while (environ[count] != NULL)
				count++;

			new_environ = malloc(sizeof(char *) * (count + 2));
			if (!new_environ)
				return;

			for (i = 0; i < count; i++)
				new_environ[i] = environ[i];

			new_environ[count] = concatenate_env(var_name, value);
			new_environ[count + 1] = NULL;

			if (environ != __environ)
				free(environ);
			environ = new_environ;
		}
	}
	else
		write(2, "setenv: Too many arguments\n", 27);
}
