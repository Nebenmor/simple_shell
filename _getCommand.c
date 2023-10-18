#include "Shell.h"
#include <stdio.h>
#include <stdlib.h>

/* Return: This is the pointer to command */
/* _getCommand: This function helps to get command inputs from  user */

char *_getCommand(void) /* _getCommand: get inputs from user */
{
	char *charcs = NULL;
	size_t numb_chars;
	ssize_t a;

	if (isatty(STDIN_FILENO))
	{
	write(STDOUT_FILENO, "$ ", 2); /* Print a shell prompt */
	}

	a = getline(&charcs, &numb_chars, stdin);

	if (a == -1)
	{
	free(charcs); /* This free the memory allocated */
	return (NULL); /* NULL is returned to indicate an EOF */
	}

	return (charcs); /* The input line is returned as a string */
}
