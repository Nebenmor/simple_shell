#include "Shell.h"

/**
 * _strdup - a function that duplicates a string
 * @str: a string
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
char *ptr;
int len = 0;
int i;

if (str == NULL)
return (NULL);

while (str[len])
len++;

ptr = malloc(sizeof(char) * (len + 1));
if (ptr == NULL)
return (NULL);

for (i = 0; i <= len; i++)
{
ptr[i] = str[i];
}
return (ptr);
}

/**
 * _strcmp - a function that compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 if strings are equal, > 0 if s1 is greater, < 0 if s2 is greater
 */
int _strcmp(char *s1, char *s2)
{
int cmp = 0;

int i;
for (i = 0; s1[i] && s2[i]; i++)
{
if (s1[i] != s2[i])
{
cmp = (int)(s1[i]) - (int)(s2[i]);
break;
}
}
return (cmp);
}

/**
 * _strlen - a function that returns the length of a string
 * @s: string
 * Return: the length of the string
 */
int _strlen(char *s)
{
int len = 0;

int i;

for (i = 0; s[i]; i++)
{
len++;
}
return (len);
}

/**
 * _strcat - a function that concatenates two strings
 * @dest: first string
 * @src: second string
 * Return: concatenated string
 */
char *_strcat(char *dest, char *src)
{
int dest_len = _strlen(dest);

int i;

for (i = 0; src[i]; i++)
{
dest[dest_len + i] = src[i];
}

dest[dest_len + _strlen(src)] = '\0';
return (dest);
}

/**
 * _strcpy - function that copies the string
 * @dest: destination string
 * @src: source string
 * Return: pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{

int i;
for (i = 0; src[i]; i++)
{
dest[i] = src[i];
dest[i + 1] = '\0';
}
return (dest);
}
