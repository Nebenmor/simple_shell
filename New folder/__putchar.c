#include "Shell.h"

/**
 * _putchar - Function that writes the char to stdout
 * @c: char
 * Return: 1 or -1
 */
int __putchar(char c)
{
	return (write(1, &c, 1));
}
