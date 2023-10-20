#include "main.h"

/**
 * temp  - exits the shell
 *
 * @node: data relevant (status and args)
 * Return: 0 on success
 */
int temp(data__shell *node)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (node->args[1] != NULL)
	{
		ustatus = _atoi(node->args[1]);
		is_digit = _isdigit(node->args[1]);
		str_len = _strlen(node->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;

		switch (1) {
			case 1:
				if (!is_digit || str_len > 10 || big_number)
				{
					get_error(node, 2);
					node->status = 2;
					return 1;
				}
				node->status = (ustatus % 256);
				break;
		}
	}
	return 0;
}
