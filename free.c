#include "Shell.h"
#include <stdlib.h>

/**
 * freeBuff - Function that frees the buffer
 * @buff: array of strings to be freed
 * Return: Void
 */
void freeBuff(char **buff)
{
int i;
if (buff == NULL)
return;


for (i = 0; buff[i] != NULL; i++)
{
free(buff[i]);
buff[i] = NULL;
}

free(buff);
buff = NULL;
}
