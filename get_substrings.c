#include "main.h"

/**
 * get_substrings - extracts the different commands passed using the separator ;
 * @line: the line containing the multiple commands
 *
 * Return: an array of strings which are commands to the shell
 */
char **get_substrings(char *line)
{
	int count = 0, i;
	char *token;
	char *line_copy;
	char **sub_strings;

	if (line == NULL)
		return (NULL);

	line_copy = strdup(line);
	if (!line_copy)
	{
		perror("strdup");
		return (NULL);
	}

	token = _strtok(line_copy, ";");
	while (token)
	{
		count++;
		token = _strtok(NULL, ";");
	}
	free(line_copy);

	sub_strings = malloc(sizeof(char *) * (count + 1));
	if (!sub_strings)
	{
		perror("malloc");
		return (NULL);
	}

	line_copy = strdup(line);
	if (!line_copy)
	{
		perror("strdup");
		free(sub_strings);
		return (NULL);
	}

	token = _strtok(line_copy, ";");
	for (i = 0; token; i++)
	{
		sub_strings[i] = strdup(token);
		token = _strtok(NULL, ";");
	}
	sub_strings[i] = NULL;

	free(line_copy);
	return (sub_strings);
}
