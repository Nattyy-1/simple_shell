#include "main.h"

/**
 * concatenate_env - joins a variable with it's value as a single string
 * @env_name: the name of the environmental variable
 * @env_value: the value of the envirionmental variable
 *
 * Return: pointer to newly allocated string containing the environmental variable, 
 * 	   or NULL on failure
 */
char *concatenate_env(char *env_name, char *env_value)
{
	int i = 0, j = 0;
	int name_len = 0, value_len = 0;
	char *env_variable;

	name_len = _strlen(env_name);
	value_len = _strlen(env_value);

	env_variable = malloc(name_len + value_len + 2);
	if (!env_variable)
		return (NULL);

	for (i = 0; i < name_len; i++)
		env_variable[i] = env_name[i];

	env_variable[i++] = '=';

	for (j = 0; j < value_len; j++, i++)
		env_variable[i] = env_value[j];

	env_variable[i] = '\0';

	return (env_variable);
}

