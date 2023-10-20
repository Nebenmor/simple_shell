#include "main.h"

/**
 * cmp__env_name - compares env variables names
 * with  the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if they are not equal. Another value if they are.
 */

int cmp__env_name(const char *nenv, const char *name)
{
	int i = 0;

	while (nenv[i] != '=')
	{
		switch (nenv[i] != name[i])
		{
			case 1:
				return (0);
			default:
				i++;
		}
	}
	return (i + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @__environ: environment variable
 *
 * Return: value of the environment variable if it is found.
 * In other cases, it returns NULL.
 */
char *_getenv(const char *name, char **__environ)
{
	char *ptr__env = NULL;
	int i = 0, mov = 0;

	while (__environ[i])
	{
		mov = cmp__env_name(__environ[i], name);
		switch (mov)
		{
			case 0:
				break;
			default:
				ptr__env = __environ[i];
				break;
		}
		if (mov)
			break;
		i++;
	}

	return (ptr__env + mov);
}

/**
 * __env - prints the environment variables
 *
 * @datash: data relevant.
 * Return: one on success.
 */
int __env(data__shell *datash)
{
	int i = 0, j;

	while (datash->__environ[i])
	{
		j = 0;
		while (datash->__environ[i][j])
			j++;
		write(STDOUT_FILENO, datash->__environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	datash->status = 0;

	return (1);
}
