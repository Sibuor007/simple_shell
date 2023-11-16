#include "_Shell.h"

/**
 * str_len - returns the length of a string
 *
 * @str: string whose length to check
 *
 * Return: int length of the string
 */
int str_len(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str++)
		i++;
	return (i);
}

/**
 * str_cmp - this compares two strings in a natural order
 *
 * @s1: first string input
 * @s2: second string input
 *
 * Return: negative if s1 < s2, positive if s1 > s2, 0 if s1 == s2
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 && *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * _start - checks if a string starts with a specified prefix
 *
 * @str: string to search
 * @prefix: prefix to find
 *
 * Return: address of next character of the string after the prefix or NULL
 */
char *starts_with(const char *str, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * str_cat - this concatenates two strings
 *
 * @dest: the destination buffer
 * @src: source buffer
 *
 * Return: pointer to destination buffer
 */
char *str_cat(char *dest, char *src)
{
	char *s = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (s);
}
