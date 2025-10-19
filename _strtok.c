#include "main.h"

/**
 * _strtok - returns a token from a string based on a delimiter
 * @str: the string from which tokens are extracted from
 * @delim: the characters used as delimiters
 *
 * Return: the token extracted or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *current;
	char *start;
	int i;
	int is_delim;

	if (str != NULL)
		current = str;

	if (current == NULL)
		return (NULL);

	while (*current)
	{
		is_delim = 0;

		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*current == delim[i])
			{
				is_delim = 1;
				break;
			}
		}

		if (!is_delim)
			break;
		current++;
	}

	if (*current == '\0')
		return (NULL);

	start = current;
	
	while (*current)
	{
		is_delim = 0;

		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*current == delim[i])
			{
				is_delim = 1;
			 	break;
			}
		}

		if (is_delim)
		{
			*current = '\0';
			current++;
			break;
		}
		current++;
	}
	
	return (start);
}
