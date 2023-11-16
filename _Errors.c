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
		putchar_err(str[u]);
	}
}

/**
 * putchar_err - This writes the character x to STDERR
 *
 * @x: character to print
 *
 * Return: 1 on success, on error return -1,
 * and errno is set appropriately
 */
int putchar_err(char x)
{
	static int u;
	static char buff_[BUFFER_SIZE_WRITE];

	if (x == FLUSH_BUFFER || u >= BUFFER_SIZE_WRITE)
	{
		write(2, buff_, u);
		u = 0;
	}
	if (x != FLUSH_BUFFER)
		buf[u++] = x;
	return (1);
}

/**
 * put_def_f - This writes the character x to given fd
 *
 * @c: character to print
 * @def_f: file descriptor
 *
 * Return: on success 1, on error -1 is returned,
 * and errno is set appropriately
 */
int put_def_f(char c, int def_f)
{
	static int u;
	static char buff_[BUFFER_SIZE_WRITE];

	if (c == FLUSH_BUFFER || u >= BUFFER_SIZE_WRITE)
	{
		write(def_f, buff_, u);
		u = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[u++] = c;
	return (1);
}

/**
 * puts_def_f - prints an input string
 *
 * @ptr_string: string to print
 * @def_f: file descriptor
 *
 * Return: number of chars put
 */
int puts_def_f(char *ptr_string, int def_f)
{
	int pr = 0;

	if (!ptr_string)
		return (0);

	while (*ptr_string)
	{
		pr += put_def_f(*ptr_string++, def_f);
	}
	return (pr);
}
