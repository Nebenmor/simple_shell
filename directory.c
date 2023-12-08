#include "shell.h"

/**
 * change_dir - function to change the current working directory
 * @poth: the poth to the directory to change to
 * @argument_count: the program name
 * Return: 0 for success, 1 for failure
 */
int change_dir(const char *poth, char *argument_count)
{
	if (chdir(poth) != 0)
	{
		const char *err_msg = ": 1: cd: can't cd to ";

		write(2, argument_count, s_strlen(argument_count));
		write(2, err_msg, s_strlen(err_msg));
		write(2, poth, s_strlen(poth));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

/**
 * upd_env_var - function to update environment variable after cd
 * @poth: the new current working directory poth
 * @environ: parent environment
 * Return: 0 for success, 1 for failure
 */
int upd_env_var(const char *poth, char *environ[])
{
	if (setenv("OLDPWD", s_getenv("PWD", environ), 1) != 0)
	{
		perror("setenv");
		return (1);
	}

	if (setenv("PWD", poth, 1) != 0)
	{
		perror("setenv");
		return (1);
	}

	return (0);
}
/**
 * cd_dir - function to implement cd
 * @arg_count: the flag for cd
 * @argument_count: the program name
 * @environ:parent environment
 * Return: 0 for sucees and 1 otherwise
 */
int cd_dir(const char *arg_count, char *argument_count, char *environ[])
{
	char cwd[poth_SIZE];

	if (arg_count == NULL || arg_count[0] == '\0')
	{
		const char *home = s_getenv("HOME", environ);

		if (home == NULL)
		{
			perror("cd");
			return (1);
		}
		arg_count = home;
	}
	else if (s_strcmp(arg_count, "-") == 0)
	{
		const char *prev = s_getenv("OLDPWD", environ);

		if (prev == NULL)
		{
			perror("cd");
			return (1);
		}
		arg_count = prev;
		write(1, "\n", 1);
		write(1, prev, s_strlen(prev));
	}

	if (change_dir(arg_count, argument_count) != 0)
		return (1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(1, cwd, s_strlen(cwd));
		write(1, "\n", 1);
	}
	if (upd_env_var(arg_count, environ) != 0)
		return (1);
	return (0);
}
