#include "_Shell.h"

/**
 * _strcpy - this copies a string
 *
 * @dest: destination string
 * @src: the source string
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 *
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
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
 * _puts - prints an input string
 *
 * @str: string to print
 *
 * Return: nothing
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		i++;
	}
}

/**
 * _putchar - writes the character c to strout
 *
 * @c: character to print
 *
 * Return: on success 1
 * on error, -1 is returned, and errno is set appropriately
 */
int _putchar(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRUTE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}
