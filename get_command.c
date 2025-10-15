#include "main.h"

/**
 * get_command - extracts the command from a given line
 * @line: the line from which the command is extracted from
 * @command: holds the extracted command
 *
 * Return: -1 if there is an error, otherwise 0;
 */
int get_command(char **line, char **command)
{
	(*line)[strcspn(*line, "\n")] = '\0';

	*command = strtok(*line, " ");
	if (*command == NULL)
		return (-1);

	if (strtok(NULL, " ") != NULL)
	{
		errno = ENOENT;
		return (-1);
	}
	return (0);
}
