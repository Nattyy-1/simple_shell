#include "main.h"

/**
 * build_arguments - builds the NULL-terminated argument vector for a command
 * @command: the already-extracted command name (becomes argv[0])
 * @argument_count: the number of whitespace-separated arguments
 *
 * Continues tokenizing the current _strtok string for arguments 1..n.
 *
 * Return: a heap-allocated argument vector, or NULL on failure
 */
char **build_arguments(char *command, int argument_count)
{
	char **args;
	int i;

	args = malloc(sizeof(char *) * (argument_count + 1));
	if (args == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	args[0] = strdup(command);
	if (args[0] == NULL)
	{
		perror("strdup");
		free(args);
		return (NULL);
	}
	for (i = 1; i < argument_count; i++)
	{
		args[i] = strdup(_strtok(NULL, " "));
		if (args[i] == NULL)
		{
			perror("strdup");
			while (i-- > 0)
				free(args[i]);
			free(args);
			return (NULL);
		}
	}
	args[argument_count] = NULL;
	return (args);
}

/**
 * get_command - extracts the command and its arguments from a given line
 * @line: the line from which the command is extracted from
 * @command: holds the extracted command (heap-allocated; caller frees)
 * @command_arguments: holds the arguments to the command
 *
 * Return: -1 if there is an error, otherwise 0
 */
int get_command(char **line, char **command, char ***command_arguments)
{
	int argument_count;

	(*line)[strcspn(*line, "\n")] = '\0';
	argument_count = _count_words(*line);

	*command = _strtok(*line, " ");
	if (*command == NULL)
		return (-1);

	/*
	 * _strtok returns a pointer into *line, which the caller frees
	 * separately. Duplicate it so *command owns independent memory and
	 * can be freed without double-freeing the line buffer.
	 */
	*command = strdup(*command);
	if (*command == NULL)
	{
		perror("strdup");
		return (-1);
	}

	*command_arguments = build_arguments(*command, argument_count);
	if (*command_arguments == NULL)
	{
		free(*command);
		return (-1);
	}
	return (0);
}
