#include "Shell.h"
#include <stdio.h>

/**
 * _atoi - converts strings to integers
 * @ptr: string to convert
 * Return: converted value
 */
int _atoi(char *ptr)
{
int num = 0;
int sign = 1; /* 1 for positive, -1 for negative */

/* Handle optional sign */
if (*ptr == '-')
{
sign = -1;
ptr++;
}
else if (*ptr == '+')
{
ptr++;
}

/* convert string to integer using a for loop */
for (; *ptr != '\0'; ptr++)
{
if (*ptr < '0' || *ptr > '9')
{
/* Invalid character encountered, return -1 as error code */
return (-1);
}
num = num * 10 + (*ptr - '0');
}

return (num *sign);
}
