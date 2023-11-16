#include "_Shell.h"

/**
 * err_atoi - this will convert a string to an integer
 *
 * @e: string to convert
 *
 * Return: 0 if no numbers in string, convert number -1 on error
 */
int err_atoi(char *e)
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
 * p_error - This prints error messages
 *
 * @info_: the parameter & return info struct
 * @s: string containing specified error type
 *
 * Return: 0 if no numbers in string, -1 if on error
 */
void p_error(_info_pass_t *info_, char *s)
{
	puts_err(info_->_filename);
	puts_err(": ");
	p_delim(info_->_counts_line, STDERR_FILENO);
	puts_err(": ");
	puts_err(info_->_argv[0]);
	puts_err(": ");
	puts_err(s);
}

/**
 * p_delim - this prints a decimal number
 *
 * @indus: input parameter
 * @fd: file descriptor
 *
 * Return: number of char to print
 */
int p_delim(int indus, int fd)
{
	int (*e)(char) = putchar_;
	int i, record = 0;
	unsigned int a, new;

	if (fd == STDERR_FILENO)
		e = putchar_err;
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
 * convert_num - converts function, a itoa clone
 *
 * @digit: integer
 * @b: base
 * @flags: arguments flags
 *
 * Return: string
 */
char *convert_num(long int digit, int b, int flags)
{
	static char *_array;
	static char buffer_[50];
	char u = 0;
	char *ptr_;
	unsigned long x = digit;

	if (!(flags & UNSIGNED_CONVERSION) && digit < 0)
	{
		x = -digit;
		u = '-';
	}

<<<<<<< HEAD
	_array = flags & _TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr_ = &buffer_[49];
	ptr_ = '\0';
=======
	array = flags & _TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
>>>>>>> origin/master

	do {
		*--ptr_ = _array[x % b];
		x /= b;
	} while (x != 0);

	if (u)
		*--ptr_ = u;
	return (ptr_);
}

/**
 * rm_comments - this removes comments, replaces '#' with '\0'
 *
 * @b: string address
 *
 * Return: 0 always
 */
void rm_comments(char *b)
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
