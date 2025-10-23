#include "main.h"

/**
 * unset_env - unsets an environmental variable based on the name it's given
 * @command_arguments: the list of variables to be unset
 */
void unset_env(char **command_arguments)
{
	int i, j, k, count, idx;
	char *environ_var_name;
	char *unset_var_name;
	char *env;
	char **new_environ;
	char **old_environ;

	i = 1;

	if (command_arguments[0] && !command_arguments[1])
	{
		write(2, "unsetenv: Too few arguments\n", 28);
	}
	else
	{
		while (command_arguments[i] != NULL)
		{
			unset_var_name = command_arguments[i];
			j = 0;

			while (environ[j] != NULL)
			{
				env = strdup(environ[j]);
				if (!env)
				{
					perror("strdup");
					return;
				}

				environ_var_name = _strtok(env, "=");

				if (_strcmp(unset_var_name, environ_var_name) == 0)
				{
					count = 0;
					while (environ[count] != NULL)
						count++;

					new_environ = malloc(sizeof(char *) * count);
					if (!new_environ)
					{
						perror("malloc");
						free(env);
						return;
					}

					idx = 0;
					for (k = 0; k < count; k++)
					{
						if (k == j)
							continue;
						new_environ[idx++] = environ[k];
					}

					new_environ[idx] = NULL;
					free(env);

					old_environ = environ;
					environ = new_environ;
					free(old_environ);

					break;
				}
				else
				{
					free(env);
					j++;
				}
			}
			i++;
		}
	}
}

