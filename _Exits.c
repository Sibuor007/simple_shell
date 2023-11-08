#include "_Shell.h"

/**
 **str_n_cpy - function that copies a string
*@dest_s: destination string
*@src_s: source string
*@size: number of copied characters
*Return: pointer to the final string
*/

char *str_n_cpy(char *dest_s, char *src_s, int size)
{
	int x, y;
	char *str = dest_s;

	x = 0;
	while (src_s[x] != '\0' && x < size - 1)
	{
		dest_s[x] = src_s[x];
		x++;
	}
	if (x < size)
	{
		y = x;
		while (y < size)
		{
			dest_s[y] = '\0';
			y++;
		}
	}
	return (str);
}

/**
 **str_n_cat - function that combines two strings
*@dest_s: the destination string
*@src_s: the source string
*@size: amount of used bytes
*Return: the combined string
*/

char *str_n_cat(char *dest_s, char *src_s, int size)
{
	int x, y;
	char *str = dest_s;

	x = 0;
	y = 0;
	while (dest_s[x] != '\0')
	x++;
	while (src_s[y] != '\0' && y < size)
	{
		dest_s[x] = src_s[y];
		x++;
		y++;
	}
	if (y < size)
	dest_s[x] = '\0';
	return (str);
}

/**
 **str_chr - used to locate a character
*@str: the string
*@c: the character in question
*Return: a pointer to the string
*/

char *str_chr(char *str, char c)
{
	do {
		if (*str == c)
		return (str);
	} while (*str++ != '\0');

	return (NULL);
}
