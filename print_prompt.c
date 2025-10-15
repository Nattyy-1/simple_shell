#include "main.h"

/**
 * print_prompt - prints the shell prompt by checking if it is a terminal
 * @line: the buffer pointer to hold the input command to the shell
 * @len: the length of the buffer
 *
 * Return: -1 if error, otherwise zero
 */
int print_prompt(char **line, size_t *len)
{
	ssize_t nread;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "($) ", 4);

	nread = getline(line, len, stdin);
	if (nread == -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);

		return (-1);
	}

	return (0);
}
