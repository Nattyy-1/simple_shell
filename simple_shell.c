#include "main.h"

/**
 * main - a simple shell program that executes a single command without
 *	 the arguments
 * @argc: the number of command line arguments
 * @argv: the list of arguments passed to main
 *
 * Return: 0 if successful, otherwise non-zero
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL, *command, **command_arguments;
	size_t len = 0;
	struct stat st;
	pid_t child_pid;
	int status, i;

	while (1)
	{
		if (print_prompt(&line, &len) == -1)
			break;

		if (get_command(&line, &command, &command_arguments) == -1)
		{
			continue;
		}

		if (stat(command, &st) == -1)
		{
			perror(argv[0]);
			continue;
		}

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			break;
		}
		if (child_pid == 0)
		{
			if (execute_command(&command, &command_arguments) == -1)
				_exit(1);
		}
		else
			wait(&status);
		for (i = 0; command_arguments[i] != NULL; i++)
			free(command_arguments[i]);
		free(command_arguments);
	}
	free(line);
	return (0);
}
