#include "Shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Comments - Function that handles shell comments (#)
 * @cmd: command
 * Return: Void
 */
void Comments(char ***cmd)
{
int i = 0;
int j;
int commentIndex = -1;

if (!(*cmd))
return;

while ((*cmd)[i])
{
if ((*cmd)[i][0] == '#' && i == 0)
{
freeBuff(*cmd);
*cmd = NULL;
return;
}
else if ((*cmd)[i][0] == '#')
{
commentIndex = i;
break;
}
i++;
}

if (commentIndex != -1)
{
free((*cmd)[commentIndex]);
(*cmd)[commentIndex] = NULL;
}

/* Optional: Removes empty elements if any after comments has been removed */



for (j = 0; (*cmd)[j]; j++)
{


if ((*cmd)[j])
{

int newLength = 0;

(*cmd)[newLength] = (*cmd)[j];
newLength++;
}
}
{
int newLength = 0;
(*cmd)[newLength] = NULL;
}
}
