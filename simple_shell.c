#include "main.h"

/**
 * main - a simple shell program that executes multiple commands separated by ';'
 * @argc: the number of command line arguments
 * @argv: the list of arguments passed to main
 *
 * Return: 0 if successful, otherwise non-zero
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL, *command, **command_arguments;
	char **sub_strings;
	size_t len = 0;
	pid_t child_pid;
	int status, i, j, last_exit_code = 0;

	while (1)
	{
		if (print_prompt(&line, &len) == -1)
			break;

		sub_strings = get_substrings(line);
		if (!sub_strings)
			continue;

		for (i = 0; sub_strings[i] != NULL; i++)
		{
			if (get_command(&sub_strings[i], &command, &command_arguments) == -1)
				continue;

			if (is_builtin(command))
			{
				handle_builtin(command, last_exit_code, command_arguments, argv[0]);
				for (j = 0; command_arguments[j] != NULL; j++)
					free(command_arguments[j]);
				free(command_arguments);
				free(command);
				continue;
			}

			if (check_path(&command) == -1)
			{
				write(STDERR_FILENO, argv[0], _strlen(argv[0]));
				write(STDERR_FILENO, ": ", 2);
				write(STDERR_FILENO, command, _strlen(command));
				write(STDERR_FILENO, ": not found\n", 12);
				free(command);
				for (j = 0; command_arguments[j] != NULL; j++)
					free(command_arguments[j]);
				free(command_arguments);
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
			{
				wait(&status);
				last_exit_code = WEXITSTATUS(status);
			}

			for (j = 0; command_arguments[j] != NULL; j++)
				free(command_arguments[j]);
			free(command_arguments);
			free(command);
		}

		for (i = 0; sub_strings[i] != NULL; i++)
			free(sub_strings[i]);
		free(sub_strings);
	}

	free(line);
	return (0);
}

