#include "shell.h"

/**
 * delete_comments - user generated function to delete comments
 * @cmd: represents the command of user
 * Return: void
 **/

void delete_comments(char *cmd);

void delete_comments(char *cmd)
{
	int index;
	int qou;

	index = 0;
	qou = 0;

	for (; cmd[index] != '\0'; index++)
	{
		if (cmd[index] == '"')
		qou = !qou;

	else if (!qou && cmd[index] == '#' && is_word_start_check(cmd, index))
	{
	cmd[index] = '\0';
	break;
	}

	}
}

/**
 * IntStr - user generatd function to convert integer to string
 * @val: the integer
 * @strr: a char pointer variable pointing to a string
 * @size: the length
 * Return: void
 */

void IntStr(int val, char *strr, int size);
void IntStr(int val, char *strr, int size)
{
int index = size - 1;

strr[index] = '\0';

while (val != 0 && index > 0)
{
	index--;
	strr[index] = '0' + (val % 10);
	val /= 10;
	}
}


/**
 * StrCpyM - function to copy string base on number of memory
 * @beginning: where to copy from
 * @n: number of memory
 * Return: the copy memory
 */

char *StrCpyM(char *beginning, size_t n);
char *StrCpyM(char *beginning, size_t n)
{
	char *end = NULL;

	size_t i;
	size_t length;

	i = 0;
	length = 0;


	while (beginning[length] != '\0' && length < n)
	{
		length++;
	}

	end = (char *)realloc(NULL, length + 1);

	if (end)
	{
		while (i < length)
		{
			end[i] = beginning[i];
			i++;
		}

		end[length] = '\0';
	}

	return (end);
}


/**
 * s_isalnum - function that checks for alphanumeric characters
 * @c: is the  character
 * Return: the absolute int
 */

int s_isalnum(unsigned char c);
int s_isalnum(unsigned char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') || (c == '_'));
}
