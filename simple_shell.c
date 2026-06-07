#include "main.h"

/**
 * run_command - parses and runs a single command string
 * @sub_string: the command text (one ';'-separated segment)
 * @shell_name: argv[0], used for error messages
 * @last_exit_code: the exit status of the previous command
 *
 * Return: the exit status to carry forward
 */
int run_command(char *sub_string, char *shell_name, int last_exit_code)
{
	char *command, **command_arguments;
	pid_t child_pid;
	int status;

	if (get_command(&sub_string, &command, &command_arguments) == -1)
		return (last_exit_code);

	if (is_builtin(command))
	{
		handle_builtin(command, last_exit_code, command_arguments, shell_name);
		free_command(command, command_arguments);
		return (last_exit_code);
	}

	if (check_path(&command) == -1)
	{
		write(STDERR_FILENO, shell_name, _strlen(shell_name));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, command, _strlen(command));
		write(STDERR_FILENO, ": not found\n", 12);
		free_command(command, command_arguments);
		return (last_exit_code);
	}

	child_pid = fork();
	if (child_pid == -1)
		perror("fork");
	else if (child_pid == 0)
	{
		if (execute_command(&command, &command_arguments) == -1)
			_exit(1);
	}
	else
	{
		wait(&status);
		last_exit_code = WEXITSTATUS(status);
	}
	free_command(command, command_arguments);
	return (last_exit_code);
}

/**
 * main - a simple shell that runs commands separated by ';'
 * @argc: the number of command line arguments
 * @argv: the list of arguments passed to main
 *
 * Return: 0 if successful, otherwise non-zero
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *line = NULL;
	char **sub_strings;
	size_t len = 0;
	int i, last_exit_code = 0;

	while (1)
	{
		if (print_prompt(&line, &len) == -1)
			break;

		handle_comment(&line);
		sub_strings = get_substrings(line);
		if (!sub_strings)
			continue;

		for (i = 0; sub_strings[i] != NULL; i++)
			last_exit_code = run_command(sub_strings[i], argv[0],
					last_exit_code);

		for (i = 0; sub_strings[i] != NULL; i++)
			free(sub_strings[i]);
		free(sub_strings);
	}

	free(line);
	return (0);
}
