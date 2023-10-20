#include "main.h"

/**
 * Exec__line - finds builtins and commands
 *
 * @node: data relevant (args)
 * Return: 1 on success.
 */
int Exec__line(data__shell *node)
{
	int (*builtin)(data__shell *node);

	switch (node->args[0] != NULL)
	{case 1:
			builtin = get_builtin(node->args[0]);
			switch (builtin != NULL)
			{case 1:
					return (builtin(node));
				default:
					return (cmd_exec(node));
			}
		default:
			return (1);
	}
}
