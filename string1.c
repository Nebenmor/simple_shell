#include "shell.h"

/**
 * custom_string_duplicate - function to duplicate a custom_string
 * @custom_string: the custom_string to copy
 * Return: the custom_string back
 */
char *custom_string_duplicate(const char *custom_string)
{
	int len = custom_string_length(custom_string);
	char *copy;

	if (custom_string == NULL)
		return (NULL);

	copy = malloc(len + 1);

	if (copy == NULL)
		return (NULL);

	custom_string_copy(copy, custom_string);
	return (copy);
}
/**
 * custom_string_length - function to return the length of custom_string
 * @custom_string: the custom_string
 * Return: the length of the custom_string
 */
int custom_string_length(const char *custom_string)
{
	int index = 0;

	while (custom_string[index] != '\0')
		index++;
	return (index);
}

/**
 * custom_string_cspan - function that return the index of the first occurence of char
 * @custom_string: the custom_string to search
 * @custom_chr: the character to search for
 * Return: the index of the search
 */
int custom_string_cspan(const char *custom_string, const char *custom_chr)
{
	int index = 0;

	while (custom_string[index] != '\0')
	{
		int charindex = 0;
			while (custom_chr[charindex] != '\0')
			{
				if (custom_string[index] == custom_chr[charindex])
					return (index);
				charindex++;
			}
		index++;
	}
	return (index);
}

/**
 * custom_string_copy - fuction to copy content of one custom_string to another
 * @custom_dest_string: the destination custom_string
 * @custom_src_string: the source custom_string
 * Return: pointer to destination custom_string
 */
char *custom_string_copy(char *custom_dest_string, const char *custom_src_string)
{
	while (*custom_src_string != '\0')
	{
		*custom_dest_string = *custom_src_string;
		custom_dest_string++;
		custom_src_string++;
	}

	*custom_dest_string = '\0';
	return (custom_dest_string);
}
