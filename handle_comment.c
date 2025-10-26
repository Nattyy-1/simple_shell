#include "main.h"

/**
 * handle_comment - handles shell comments
 * @line: the line containing the shell command input
 */
void handle_comment(char **line)
{
	int i = 0;

	if ((*line)[0] == '#')
	{
		(*line)[0] = '\0';
		return;
	}

	while ((*line)[i] != '\0')
	{
		if ((*line)[i] == '#')
		{
			(*line)[i] = '\0';
			break;
		}
		i++;
	}
}

