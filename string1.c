#include "shell.h"

/**
 * s_strdup - this function copies string
 * @string: this is the string to copy
 * Return: the string back
 */

char *s_strdup(const char *string);
char *s_strdup(const char *string)
{
	int len = s_strlen(string);
	char *copying;

	if (string == NULL)
		return (NULL);

	copying = realloc(NULL, (len + 1));

	if (copying == NULL)
		return (NULL);

	s_strcpy(copying, string);
	return (copying);
}


/**
 * s_strlen - this function returns the length of string
 * @string: the string
 * Return: the length of the string
 */

int s_strlen(const char *string);
int s_strlen(const char *string)
{
	int index = 0;

	while (string[index] != '\0')
		index++;
	return (index);
}

/**
 * s_strcspn - function that return the index of the first occurence of char
 * @string: the string to search
 * @chr: the character to search for
 * Return: the index of the search
 */

int s_strcspn(const char *string, const char *chr);
int s_strcspn(const char *string, const char *chr)
{
	int index;

	for (index = 0; string[index] != '\0'; index++)
	{
		int charindex = 0;
			while (chr[charindex] != '\0')
			{
				if (string[index] == chr[charindex])
					return (index);
				charindex++;
			}
		index++;
	}
	return (index);
}

/**
 * s_strcpy - fuction to copy content of one string to another
 * @dest_string: the destination string
 * @src_string: the source string
 * Return: pointer to destination string
 */

char *s_strcpy(char *dest_string, const char *src_string);
char *s_strcpy(char *dest_string, const char *src_string)
{
	while (*src_string != '\0')
	{
		*dest_string = *src_string;
		dest_string++;
		src_string++;
	}

	*dest_string = '\0';
	return (dest_string);
}
