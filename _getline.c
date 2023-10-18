#include "Shell.h"
#include <stdlib.h>

/**
 * _getline - Function that gets a line from user/file
 * @line: Pointer to store the line
 * @buffsize: Size of the buffer
 * @stream: File descriptor
 * Return: Number of characters read, -1 on failure.
 */
ssize_t _getline(char **line, size_t *buffsize, FILE *stream)
{
size_t num_chars = 0;
char chars;
char *temp;

if (*line == NULL || *buffsize == 0)
{
*buffsize = MAX_INPUT_SIZE;
*line = (char *)malloc(*buffsize);
if (*line == NULL)
return (-1);
}

for (;;)
{
chars = fgetc(stream);
if (chars == '\n' || chars == EOF)
{
(*line)[num_chars] = '\0';
break;
}

(*line)[num_chars] = chars;
num_chars++;

if (num_chars >= *buffsize)
{
*buffsize *= 2;
temp = (char *)realloc(*line, *buffsize);
if (temp == NULL)
return (-1);
*line = temp;
}
}

return (num_chars);
}

