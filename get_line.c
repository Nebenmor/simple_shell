#include "main.h"

/**
 * bring__line - assigns the line var for get_line
 * @linptr: Buffer that stores the input str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer.
 */
void bring__line(char **linptr, size_t *n, char *buffer, size_t j)
{
	int choice = 0;

	switch (*linptr == NULL)
	{case 1:
			if (j > BUFSIZE)
				*n = j;
			else
				*n = BUFSIZE;
			*linptr = buffer;
			choice = 1;
			break;
	}
	switch (*n < j)
	{case 1:
			if (j > BUFSIZE)
				*n = j;
			else
				*n = BUFSIZE;
			*linptr = buffer;
			choice = 1;
			break;
	}

	switch (choice)
	{case 0:
			_strcpy(*linptr, buffer);
			free(buffer);
	}
}

/**
 * get_line - Read input from str_eam
 * @linptr: buffer that stores the input
 * @n: size of linptr
 * @str_eam: str_eam to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **linptr, size_t *n, FILE *str_eam)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	switch (input)
	{case 0:
			fflush(str_eam);
			break;
		default:
			return (-1);
	}
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);

	switch (buffer == 0)
	{case 1:
			return (-1);
	}

	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);

		switch (i)
		{case -1:
			case 0:
				if (i == -1 || (i == 0 && input == 0))
				{
					free(buffer);
					return (-1);
				}

				if (i == 0 && input != 0)
				{
					input++;
					break;
				}

				if (input >= BUFSIZE)
					buffer = _realloc(buffer, input, input + 1);
				buffer[input] = t;
				input++;
		}
	}

	buffer[input] = '\0';
	bring__line(linptr, n, buffer, input);
	retval = input;

	if (i != 0)
		input = 0;

	return (retval);
}
