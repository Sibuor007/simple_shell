#include "_Shell.h"

/**
 * str_n_cpy - function that copies a string
 *
 * @dests: destination string
 * @src: string source
 * @x: the amount of chars to copy
 *
 * Return: the concatenated string
 */

char* str_n_cpy(char *dests, char *src, int x)
{
	int i, j;
	char *str = dests;

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
	return (str);
}

/**
 * str_n_cat - function that concatenates two strings
 *
 * @dests: first string input
 * @src: second string input
 * @x: amount of bytes to be maximally used
 *
 * Return: the concatenated string
 */

char* str_n_cat(char *dests, char *src, int x)
{
	int i, j;
	char *str = dests;

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
	return (str);
}

/**
 * str_n_chr - function that locates a string character
 *
 * @str: string to parse
 * @c: character
 *
 * Return: a pointer to the memory area str
 */

char* str_n_chr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
