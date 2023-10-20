#include "Shell.h"
#include <stdlib.h>

/**
 * tokenCmd - Function that tokenizes a string
 * @line: String to tokenize
 * Return: Array of tokens
 */
char **tokenCmd(char *line)
{
char *buff = NULL;
char **command = NULL;
char *copy = NULL;
int i = 0, j;

copy = _strdup(line);
buff = strtok(line, delim);
if (buff == NULL)
{
free(copy);
return (NULL);
}

for (; buff != NULL; i++)
{
buff = strtok(NULL, delim);
}
free(line);
command = malloc(sizeof(char *) * (i + 1));
buff = strtok(copy, delim);

for (j = 0; buff != NULL; j++)
{
command[j] = _strdup(buff);
buff = strtok(NULL, delim);
}
command[j] = NULL;
free(copy);

return (command);
}
