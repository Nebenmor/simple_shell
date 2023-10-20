#include "main.h"

/**
 * fre__date - frees data structure
 *
 * @node: data  structure
 * Return: no return
 */
void fre__date(data__shell *node)
{
	unsigned int i;

	for (i = 0; node->__environ[i]; i++)
	{
		free(node->__environ[i]);
	}

	free(node->__environ);
	free(node->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @node: data structure
 * @aev: argument vector
 * Return: no return
 */
void set_data(data__shell *node, char **aev)
{
	unsigned int i;

	node->aev = aev;
	node->input = NULL;
	node->args = NULL;
	node->status = 0;
	node->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	node->__environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		node->__environ[i] = _strdup(environ[i]);
	}

	node->__environ[i] = NULL;
	node->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @aec: argument count
 * @aev: argument vector
 *
 * Return: 0 on success.
 */
int main(int aec, char **aev)
{
	data__shell node;
	(void) aec;

	signal(SIGINT, get_sigint);
	set_data(&node, aev);
	shell(&node);
	fre__date(&node);
	if (node.status < 0)
		return (255);
	return (node.status);
}
