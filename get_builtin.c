#include "main.h"

/**
 * git__builtin -  builtin that parses the command in the arg
 * @commnd: command
 * Return: function pointer of the builtin command.
 */
int (*git__builtin(char *commnd))(data__shell *)
{
	builtin_t builtin[] = {
		{ "env", __env },
		{ "exit", temp },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i = 0;

	while (builtin[i].name)
	{
		if (_strcmp(builtin[i].name, commnd) == 0)
			break;
		i++;
	}

	return (builtin[i].f);
}
