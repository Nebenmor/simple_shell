#include "Shell.h"

/*
 * _putchar - This is a function that writes the char to the standard output
 * @c: This represents char character
 * Return: 1 or -1 on success or failure respectively
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
