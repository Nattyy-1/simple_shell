#include "main.h"

/**
 * get_command - extracts the command and its arguments from a given line
 * @line: the line from which the command is extracted from
 * @command: holds the extracted command
 * @command_arguments: holds the arguments to the command
 *
 * Return: -1 if there is an error, otherwise 0;
 */
int get_command(char **line, char **command, char ***command_arguments)
{
	int argument_count;
	int i;

	(*line)[strcspn(*line, "\n")] = '\0';

	argument_count = _count_words(*line);

	*command = strtok(*line, " ");
	if (*command == NULL)
		return (-1);

	*command_arguments = malloc(sizeof(char *) * (argument_count + 1));
	if (*command_arguments == NULL)
	{
		perror("malloc");
		return (-1);
	}

	(*command_arguments)[0] = strdup(*command);
	if ((*command_arguments)[0] == NULL)
	{
		perror("strdup");
		free(*command_arguments);
		return (-1);
	}

	for (i = 1; i < argument_count; i++)
	{
		(*command_arguments)[i] = strdup(strtok(NULL, " "));
		if ((*command_arguments)[i] == NULL)
		{
			perror("strdup");
			while (i-- > 0)
				free((*command_arguments)[i]);
			free(*command_arguments);
			return (-1);
		}
	}

	(*command_arguments)[argument_count] = NULL;

	return (0);
}
