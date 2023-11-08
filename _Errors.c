#include "_Shell.h"

/**
 * puts_err - This prints an input string
 *
 * @str: string to print
 *
 * Return: nothing
 */
void puts_err(char *str)
{
	int u = 0;

	if (!str)
		return;
	while (str[u] != '\0')
	{
		err_putchar (str[u]);
	}
}

/**
 * err_putchar - This writes the character x to STDERR
 *
 * @x: character to print
 *
 * Return: 1 on success, on error return -1,
 * and errno is set appropriately
 */
int err_putchar(char x)
{
	static int u;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write (2, buf, u);
		u = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}

/**
 * _givefd - This writes the character x to given fd
 *
 * @x: character to print
 * @fd: file descriptor
 *
 * Return: on success 1, on error -1 is returned,
 * and errno is set appropriately
 */
int _givefd (char x, int fd)
{
	static int u;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || u >= WRITE_BUF_SIZE)
	{
		write (fd, buf, u);
		u = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}

/**
 * _printfd - prints an input string
 *
 * @str: string to print
 * @fd: file descriptor
 *
 * Return: number of chars put
 */
int _printfd(char *str, int fd)
{
	int pr = 0;

	if (!str)
		return (0);

	while (*str)
	{
		pr+= _printfd(*str++, fd);
	}
	return (pr);
}
