#include "main.h"

/**
 * without_comment -  deletes comments from the input
 *
 * @in: input string
 * Return: input without comments.
 */
char *without_comment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		switch (in[i])
		{
			case '#':
				if (i == 0)
				{
					free(in);
					return (NULL);
				}
				if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
					up_to = i;
				break;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell - Loop of shell
 * @node: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell(data__shell *node)
{
	int i_eof;
	char *input;

	for (int loop = 1; loop == 1;)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			switch (check_syntax_error(node, input))
			{
				case 1:
					node->status = 2;
					free(input);
					continue;
			}

			input = rep_var(input, node);
			loop = split_commands(node, input);
			node->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
