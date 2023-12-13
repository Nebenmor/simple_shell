#include "shell.h"

/**
 * s_realloc - Reallocates a memory block using realoc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
*/

void *s_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *s_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *memo;
	char *ptr_copy, *filler;
	unsigned int index;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		memo = realloc(NULL, (new_size));
		if (memo == NULL)
			return (NULL);

		return (memo);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	memo = realloc(NULL, ((sizeof(*ptr_copy) * new_size)));
	if (memo == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = memo;

	for (index = 0; index < old_size && index < new_size; index++)
		filler[index] = *ptr_copy++;

	free(ptr);
	return (memo);
}

/**
 * assigns_lineptr - function that reassigns the lineptr variable for _getline.
 * @lineptr:is a  buffer to store an input string.
 * @n: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */

void assigns_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
void assigns_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		s_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * s_getline - Reads input from a stream.
 * @lineptr: A buffer to store the input.
 * @n: The size of lineptr.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */

ssize_t s_getline(char **lineptr, size_t *n, FILE *stream);
ssize_t s_getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;
	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = s_realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';
	assigns_lineptr(lineptr, n, buffer, input);
	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
