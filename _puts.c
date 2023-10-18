#include "Shell.h"

/*
 * _puts: This function prints a string followed by a new line
 * @str: This is a pointer to a string
 * Return: none
 */

void _puts(char *str) /* calls the _puts function */
{
	while (*str != '\0')
	{
	_putchar(*str); /* The _putchar function is called to print each character */
	str++; /* post Increment */
	}
_putchar('\n'); /* Follows the string with a new line on printing */
}
