#include "Shell.h"
#include <string.h>

/**
 * _env - Function that gets an environment
 * @args: argument
 * Return: env
 */
char *_env(char *args)
{
char *env1;
int i = 0;

while (environ[i] != NULL)
{
char *tmp = _strdup(environ[i]);
char *sign = strtok(tmp, "=");

if (_strcmp(sign, args) == 0)
{
env1 = _strdup(strtok(NULL, "\n"));
free(tmp);
return (env1);
}

free(tmp);
i++;
}

return (NULL);
}

