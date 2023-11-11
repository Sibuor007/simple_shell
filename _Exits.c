#include "_Shell.h"

/**
 * _strcpy - function that copies a string
 *
 * @dests: destination string
 * @src: string source
 * @x: the amount of chars to copy
 *
 * Return: the concatenated string
 */

char _strcpy(char *dests, char *src, int x)
{
	int i, j;
	char *s = dests;

	i = 0;
	while (src[i] != '\0' && i < x - 1)
	{
		dests[i] = src[i];
		i++;
	}
	if (i < x)
	{
		j = i;
		while (j < x)
		{
			dests[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strcat - function that concatenates two strings
 *
 * @dests: first string input
 * @src: second string input
 * @x: amount of bytes to be maximally used
 *
 * Return: the concatenated string
 */

char _strcat(char *dests, char *src, int x)
{
	int i, j;
	char *s = dests;

	i = 0;
	j = 0;
	while (dests[i] != '\0')
		i++;

	while (src[j] != '\0' && j < x)
	{
		dests[i] = src[j];
		i++;
		j++;
	}
	if (j < x)
		dests[i] = '\0';
	return (s);
}

/**
 * _strchr - function that locates a string character
 *
 * @s: string to parse
 * @c: character
 *
 * Return: a pointer to the memory area s
 */

char _strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
