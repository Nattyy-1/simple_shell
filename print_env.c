#include "main.h"

/**
 * print_env - prints the enviromental variables set in the system
 */
void print_env(void)
{
	int i = 0;

	if (environ == NULL)
		return;

	while (environ[i] != NULL)
	{
		write(1, environ[i], _strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
}
