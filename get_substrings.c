#include "main.h"

/**
 * count_commands - counts the ';'-separated commands in a line
 * @line: the line to inspect
 *
 * Return: the number of commands, or -1 on allocation failure
 */
int count_commands(char *line)
{
	int count = 0;
	char *token;
	char *line_copy;

	line_copy = strdup(line);
	if (!line_copy)
	{
		perror("strdup");
		return (-1);
	}
	token = _strtok(line_copy, ";");
	while (token)
	{
		count++;
		token = _strtok(NULL, ";");
	}
	free(line_copy);
	return (count);
}

/**
 * get_substrings - splits a line into commands using ';' as separator
 * @line: the line containing the multiple commands
 *
 * Return: an array of strings which are commands to the shell
 */
char **get_substrings(char *line)
{
	int count, i;
	char *token;
	char *line_copy;
	char **sub_strings;

	if (line == NULL)
		return (NULL);

	count = count_commands(line);
	if (count == -1)
		return (NULL);

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
