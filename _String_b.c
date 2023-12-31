#include "_Shell.h"

/**
 * str_cpy - this copies a string
 *
 * @dest: destination string
 * @src: the source string
 *
 * Return: pointer to destination
 */
char *str_cpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * str_up - duplicates a string
 *
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *str_up(const char *str)
{
	int len = 0;
	char *s;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	for (len++; len--;)
		s[len] = *--str;
	return (s);
}

/**
 * puts_ - prints an input string
 *
 * @str: string to print
 *
 * Return: nothing
 */
void puts_(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		putchar_(str[x]);
		x++;
	}
}

/**
 * putchar_ - writes the character c to strout
 *
 * @c: character to print
 *
 * Return: on success 1
 * on error, -1 is returned, and errno is set appropriately
 */
int putchar_(char c)
{
	static int i;
	static char buffer[BUFFER_SIZE_WRITE];

	if (c == FLUSH_BUFFER || i >= BUFFER_SIZE_WRITE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buffer[i++] = c;
	return (1);
}
