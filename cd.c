#include "main.h"

/**
 * cd_error - prints a "can't cd to" error message
 * @shell_name: the name of the shell program
 * @path: the path that could not be reached
 */
void cd_error(char *shell_name, char *path)
{
	write(2, shell_name, _strlen(shell_name));
	write(2, ": cd: can't cd to ", 18);
	write(2, path, _strlen(path));
	write(2, "\n", 1);
}

/**
 * cd_home - changes the working directory to $HOME
 * @shell_name: the name of the shell program
 */
void cd_home(char *shell_name)
{
	char *path;
	char old_wd[PATH_MAX];

	path = getenv("HOME");
	getcwd(old_wd, sizeof(old_wd));
	if (path == NULL)
		return;
	if (chdir(path) != 0)
	{
		cd_error(shell_name, path);
		return;
	}
	setenv("PWD", path, 1);
	setenv("OLDPWD", old_wd, 1);
}

/**
 * cd_previous - changes the working directory to $OLDPWD
 * @old_wd: the current working directory before the change
 * @shell_name: the name of the shell program
 */
void cd_previous(char *old_wd, char *shell_name)
{
	char *path;

	path = getenv("OLDPWD");
	if (!path)
	{
		write(2, shell_name, _strlen(shell_name));
		write(2, ": cd: OLDPWD not set\n", 21);
		return;
	}
	if (chdir(path) != 0)
	{
		cd_error(shell_name, path);
		return;
	}
	write(1, path, _strlen(path));
	write(1, "\n", 1);
	setenv("PWD", path, 1);
	setenv("OLDPWD", old_wd, 1);
}

/**
 * cd - changes the current working directory
 * @command_arguments: the arguments passed to cd
 * @shell_name: the name of the shell program
 */
void cd(char **command_arguments, char *shell_name)
{
	char *path;
	char old_wd[PATH_MAX];

	if (command_arguments[0] && !command_arguments[1])
	{
		cd_home(shell_name);
		return;
	}
	path = command_arguments[1];
	getcwd(old_wd, sizeof(old_wd));
	if (_strcmp(path, "-") == 0)
	{
		cd_previous(old_wd, shell_name);
		return;
	}
	if (chdir(path) != 0)
	{
		cd_error(shell_name, path);
		return;
	}
	setenv("OLDPWD", old_wd, 1);
	setenv("PWD", getcwd(old_wd, sizeof(old_wd)), 1);
}
