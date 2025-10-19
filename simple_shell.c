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
	pid_t child_pid;
	int status, i, last_exit_code = 0;

	while (1)
	{
		if (print_prompt(&line, &len) == -1)
			break;
		if (get_command(&line, &command, &command_arguments) == -1)
		{
			continue;
		}
		if (is_builtin(command))
		{
			handle_builtin(command, last_exit_code);
			for (i = 0; command_arguments[i] != NULL; i++)
				free(command_arguments[i]);
			free(command_arguments);
			continue;
		}
		if (check_path(&command) == -1)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, command, _strlen(command));
			write(STDERR_FILENO, ": not found\n", 12);
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
		for (i = 0; command_arguments[i] != NULL; i++)
			free(command_arguments[i]);
		free(command_arguments);
		free(command);
	}
	free(line);
	return (0);
}
