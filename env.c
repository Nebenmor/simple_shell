#include "shell.h"
/**
 * no_len - Counts the digit length of a number.
 * @n: The number to measure.
 *
 * Return: The digit length.
 */
int no_len(int n)
{
	unsigned int numm;
	int len;

	len = 1;

	if (n < 0)
	{
		len++;
		numm = n * -1;
	}
	else
	{
		numm = n;
	}

	for (; numm > 9; len++)
	{
		numm /= 10;
	}

	return (len);
}


/**
 * _itoa - Converts an integer to a string.
 * @n: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int n)
{
	char *buff;
	unsigned int numm;
	int len;

	len = no_len(n);


	buff = realloc(NULL, sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);

	buff[len] = '\0';

	if (n < 0)
	{
		numm = n * -1;
		buff[0] = '-';
	}
	else
	{
		numm = n;
	}

	len--;

	while (numm > 0)
		{
		buff[len] = (numm % 10) + '0';
		numm /= 10;
		len--;
		}

	free(buff);
	return (buff);
}
