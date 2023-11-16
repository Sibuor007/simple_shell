#include "_Shell.h"

/**
 * _i_active - puts the shell into interactive mode
 * @_info: address for the structure
 * Return: 0 otherwise, 1 for success
 */

int _i_active(_info_pass_t *_info)
{
	return (isatty(STDIN_FILENO) && _info->_input_read <= 2);
}

/**
 * delim_ - confirms whether a character is a delimiter
 * @c: item to be checked
 * @d_ptr: string for the delimiter
 * Return: 0 if result is false, 1 if true
 */

int delim_(char c, char *d_ptr)
{
	while (*d_ptr)
		if (*d_ptr++ == c)
		return (1);
	return (0);
}

/**
 *is_alpha - scans for alphabetic characters
*@c: item to be checked
*Return: 0 if false, 1 if true
*/

int is_alpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/**
 *a_toi - function that converts a string to integer value
*@str: pointer to the string
*Return: result if strings are converted, 0 otherwise
*/

int a_toi(char *str)
{
	int j, mark = 1, _flag = 0, result;
	unsigned int count = 0;

	for (j = 0;  str[j] != '\0' && _flag != 2; j++)
	{
		if (str[j] == '-')
		mark *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			_flag = 1;
			count *= 10;
			count += (str[j] - '0');
		}
		else if (_flag == 1)
			_flag = 2;
	}

	if (mark == -1)
		result = -count;
	else
		result = count;

	return (result);
}
