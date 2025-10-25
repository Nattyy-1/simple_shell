#include "main.h"

/**
 * cd - changes the current directory of the process to the directory
 *       specified in the argument
 * @command_arguments: the arguments passed to cd
 * @shell_name: the name of the shell program
 */
void cd(char **command_arguments, char *shell_name)
{
	char *path;
	char old_wd[PATH_MAX];

	if (command_arguments[0] && !command_arguments[1])
	{
		path = getenv("HOME");
		getcwd(old_wd, sizeof(old_wd));

		if (path != NULL)
		{
			if (chdir(path) != 0)
			{
				write(2, shell_name, _strlen(shell_name));
				write(2, ": cd: can't cd to ", 18);
				write(2, path, _strlen(path));
				write(2, "\n", 1);
				return;
			}

			setenv("PWD", path, 1);
			setenv("OLDPWD", old_wd, 1);
		}
	}
	else
	{
		path = command_arguments[1];
		getcwd(old_wd, sizeof(old_wd));

		if (_strcmp(path, "-") == 0)
		{
			path = getenv("OLDPWD");

			if (!path)
			{
				write(2, shell_name, _strlen(shell_name));
				write(2, ": cd: OLDPWD not set\n", 21);
				return;
			}

			if (chdir(path) != 0)
			{
				write(2, shell_name, _strlen(shell_name));
				write(2, ": cd: can't cd to ", 18);
				write(2, path, _strlen(path));
				write(2, "\n", 1);
				return;
			}

			write(1, path, _strlen(path));
			write(1, "\n", 1);
			setenv("PWD", path, 1);
			setenv("OLDPWD", old_wd, 1);
		}
		else
		{
			if (chdir(path) != 0)
			{
				write(2, shell_name, _strlen(shell_name));
				write(2, ": cd: can't cd to ", 18);
				write(2, path, _strlen(path));
				write(2, "\n", 1);
				return;
			}

			setenv("OLDPWD", old_wd, 1);
			setenv("PWD", getcwd(old_wd, sizeof(old_wd)), 1);
		}
	}
}
