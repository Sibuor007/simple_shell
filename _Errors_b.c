#include "_Shell.h"

/**
 * _erratoi - this will convert a string to an integer
 *
 * @e: string to convert
 *
 * Return: 0 if no numbers in string, convert number -1 on error
 */
int _erratoi(char *e)
{
	int num = 0;
	unsigned long int record = 0;

	if (*e == '+')
		e++;
	for (num = 0; e[num] != '\0'; num++)
	{
		if (e[num] >= '0' && e[num] <= '9')
		{
			record *= 10;
			record += (e[num] - '0');
			if (record > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (record);
}

/**
 * err_print - This prints error messages
 *
 * @info: the parameter & return info struct
 * @s: string containing specified error type
 * @error_type: tupe of error
 *
 * Return: 0 if no numbers in string, -1 if on error
 */
void err_print(info_t *info, char *error_type, char *s)
{
	_errputs(info->fname);
	_errputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	_errputs(": ");
	_errputs(info->argv[0]);
	_errputs(": ");
	_errputs(error_type);
	_errputs(": ");
	_errputs(s);
}

/**
 * print_dec - this prints a decimal number
 *
 * @indus: input parameter
 * @fd: file descriptor
 *
 * Return: number of char to print
 */
int print_dec(int indus, int fd)
{
	int (*e)(char) = _putchar;
	int i, record = 0;
	unsigned int a, new;

	if (fd == STDERR_FILENO)
		e = _eputchar;
	if (indus < 0)
	{
		a = -indus;
		e('-');
		record++;
	}
	else
	{
		a = indus;
		new = a;
	}

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (a / i)
		{
			e('0' + new / i);
			record++;
		}
		new %= i;
	}
	e('0' + new);
	record++;

	return (record);
}

/**
 * convert_funcs - converts function, a itoa clone
 *
 * @digit: integer
 * @b: base
 * @flags: arguments flags
 *
 * Return: string
 */
char *convert_funcs(long int digit, int b, int flags)
{
	static char *array;
	static char buffer[50];
	char u = 0;
	char *ptr;
	unsigned long x = digit;

	if (!(flags & CONVERT_UNSIGNED) && digit < 0)
	{
		x = -digit;
		u = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = '\0';

	do {
		*--ptr = array[x % b];
		x /= b;
	} while (x != 0);

	if (u)
		*--ptr = u;
	return (ptr);
}

/**
 * remove_comment - this removes comments, replaces '#' with '\0'
 *
 * @b: string address
 *
 * Return: 0 always
 */
void remove_comment(char *b)
{
	int e;

	for (e = 0; b[e] != '\0'; e++)
	{
		if (b[e] == '#' && (!e || b[e - 1] == ' '))
		{
			b[e] = '\0';
			break;
		}
	}
}
