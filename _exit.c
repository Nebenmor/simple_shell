#include "Shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _exxit - Function that exits the shell
 * @toks: tokens
 * @buff: buffer
 * Return: int
 */
int _exxit(char **toks, char *buff)
{
int status = 0;

if (toks[1] != NULL)
{
status = _atoi(toks[1]);
if (status < 0)
{
fprintf(stderr, "./hsh: exit: %s: numeric argument required\n", toks[1]);
freeBuff(toks);
free(buff);
return (2);
}
}

freeBuff(toks);
free(buff);
exit(status);
}
