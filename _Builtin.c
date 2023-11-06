#include "_Shell.h"

/**
 * our_exit - this exits the shell
 *
 * @info: Structure containing potential arguments.
 * This is used to maintain constant function prototype.
 *
 * Return: exit with a given status 0 if info.argv[0] != "exit"
 */
int our_exit(info_t *info)
{
	int checkexit;

	if (info->argv[1]) /* if there is an exit argument */
	{
		checkexit = _erratoi(info->argv[1]);
		if (checkexit == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * our_cd - this changes the current directory of the process
 *
 * @info: Structure containing potential arguments.
 * This is used to maintain constant function prototype.
 *
 * Return: 0 always
 */
int our_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("Error: Unable to retrieve the current working directory\n");
	return (-1); /* TODO: check this part, totally not sure */

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * our_help - this changes the current directory of the process
 *
 * @info: Structure containing potential arguments.
 * This is used to maintain constant function prototype.
 *
 * Return: 0 always
 */
int our_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0);
	_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
