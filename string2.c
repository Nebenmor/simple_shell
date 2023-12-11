#include "shell.h"

/**
 * s_strchr - finds the first occurence of character in a string
 * @string: the string to search
 * @chr: the character searching for
 * Return: pointer to the search character
 */

char *s_strchr(const char *string, int chr)
{
	for (; *string != '\0'; string++)
	{
		if (*string == (char)chr)
			return ((char *)string);
	}
	return (NULL);
}

/**
 * s_strtok - this is a function that tokenize command
 * @str: the string to tokenize
 * @delim: the delimiter to make use of
 * Return: the tokenize string
 */
char *s_strtok(char *str, const char *delim)
{
	char *beginning;
	char *ending;
	static char *tokens;

	if (str != NULL)
	{
		tokens = str;
	}
	else if (tokens == NULL)
	{
		return (NULL);
	}
	for (; is_delimiter(*tokens, delim); tokens++)
	{
		/* the body */
	}
	if (*tokens == '\0')
	{
		return (NULL);
	}
	beginning = tokens;
	ending = beginning;
	while (*ending != '\0')
	{
		if (is_delimiter(*ending, delim))
		{
			*ending = '\0';
			tokens = ending + 1;
			return (beginning);
		}
		ending++;
	}
	tokens = ending;
	return (beginning);
}

/**
 * is_delimiter - function that searches for a delimiter
 * @c: the character
 * @delim: the deimiter
 * Return:1 if success and 0 otherwise
 */
int is_delimiter(char c, const char *delim)
{
	for (; *delim; delim++)
	{
		if (c == *delim)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * s_strncmp - Compare two strings.
 * @s1: Pointer to a string.
 * @s2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if s1 is shorter than s2.
 *         0 if s1 and s2 match.
 *         Greater than 0 if s1 is longer than s2.
 */
int s_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
