#include "_Shell.h"

/**
 * **_str_tow - ignores delimeter, and split strings to word
 * @ptr_string: the string
 * @dlm: the delimeter
 * Return: NULL on failure, pointer to string on success
 */

char **_str_tow(char *ptr_string, char *dlm)
{
	int x, y, o, p, size_words = 0;
	char **str;

	if (ptr_string == NULL || ptr_string[0] == 0)
	return (NULL);
	if (!dlm)
	dlm = " ";
	for (x = 0; ptr_string[x] != '\0'; x++)
	if (!delim_(ptr_string[x], dlm) &&
			(delim_(ptr_string[x + 1], dlm) || !ptr_string[x + 1]))
	size_words++;

	if (size_words == 0)
	return (NULL);
	str = malloc((1 + size_words) * sizeof(char *));
	if (!str)
	return (NULL);
	for (x = 0, y = 0; y < size_words; y++)
	{
		while (delim_(ptr_string[x], dlm))
		x++;
		o = 0;
		while (!delim_(ptr_string[x + o], dlm) && ptr_string[x + o])
		o++;
		str[y] = malloc((o + 1) * sizeof(char));
		if (!str[y])
		{
			for (o = 0; o < y; o++)
			free(str[o]);
			free(str);
			return (NULL);
		}
		for (p = 0; p < o; p++)
		str[y][p] = ptr_string[x++];
		str[y][p] = 0;
	}
	str[y] = NULL;
	return (str);
}

/**
 * **_str_tow_b - divides string to words
 * @ptr_string: the string
 * @dlm: the delimeter
 * Return: NULL on failure, point to array of string
 */

char **_str_tow_b(char *ptr_string, char dlm)
{
	int x, y, o, p, size_words = 0;
	char **str;

	if (ptr_string == NULL || ptr_string[0] == 0)
	return (NULL);
	for (x = 0; ptr_string[x] != '\0'; x++)
	if ((ptr_string[x] != dlm && ptr_string[x + 1] == dlm) ||
	(ptr_string[x] != dlm && !ptr_string[x + 1]) || ptr_string[x + 1] == dlm)
	size_words++;
	if (size_words == 0)
	return (NULL);
	str = malloc((1 + size_words) * sizeof(char *));
	if (!str)
	return (NULL);
	for (x = 0, y = 0; y < size_words; y++)
	{
		while (ptr_string[x] == dlm && ptr_string[x] != dlm)
		x++;
		o = 0;
		while (ptr_string[x + o] != dlm &&
				ptr_string[x + o] && ptr_string[x + o] != dlm)
		o++;
		str[y] = malloc((o + 1) * sizeof(char));
		if (!str[y])
		{
			for (o = 0; o < y; o++)
			free(str[o]);
			free(str);
			return (NULL);
		}
		for (p = 0; p < o; p++)
		str[y][p] = ptr_string[x++];
		str[y][p] = 0;
	}
	str[y] = NULL;
	return (str);
}
