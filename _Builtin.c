#include "_Shell.h"

int _help(_info_pass_t *info_);

/**
 * e_exit - a function that exits the simple shell
 * @info_: a structure that contains arguments
 * Return: predetermined exit status
 */

int e_exit(_info_pass_t *info_)
{
	int exit_check;

	if (info_->_argv[1])
	{
		exit_check = err_atoi(info_->_argv[1]);
		if (exit_check == -1)
		{
			info_->_status = 2;
			p_error(info_, "Invalid no.: ");
			puts_err(info_->_argv[1]);
			putchar_err('\n');
			return (1);
		}
		info_->_errno = err_atoi(info_->_argv[1]);
		return (-2);
	}
	info_->_errno = -1;
	return (-2);
}

/**
 * _cd - a function that changes directory
 * @info_: a structure that has arguments
 * Return: 0
 */

int _cd(_info_pass_t *info_)
{
	char *str, *d_var, buff_[1024];
	int _chdir;

	str = getcwd(buff_, 1024);
	if (!str)
	{
		puts_("Error: can't retrieve dir\n");
		return (-1);
	}
	if (!info_->_argv[1])
	{
		d_var = get_env(info_, "HOME: ");
		if (!d_var)
			_chdir =
			chdir((d_var = get_env(info_, "PWD: ")) ? d_var : "/");
		else
			_chdir = chdir(d_var);
	}
	else if (str_cmp(info_->_argv[1], "-") == 0)
	{
		if (!get_env(info_, "OLD_PWD: "))
		{
			puts_(str);
			putchar_('\n');
			return (1);
		}
		puts_(get_env(info_, "OLD_PWD: ")), putchar_('\n');
		_chdir =
		chdir((d_var = get_env(info_, "OLD_PWD: ")) ? d_var : "/");
	}
	else
	_chdir = chdir(info_->_argv[1]);
	if (_chdir == -1)
	{
		p_error(info_, "can't cd to ");
		puts_err(info_->_argv[1]), putchar_err('\n');
	}
	else
	{
		set_env(info_, "OLD_PWD: ", get_env(info_, "PWD="));
		set_env(info_, "PWD", getcwd(buff_, 1024));

	}
	return (0);
}

/**
 * _help - invokes change to the current process
 * @info_: a structure that contains arguments
 *  Return: 0
 */

int _help(_info_pass_t *info_)
{
	char **arr_args;

	arr_args = info_->_argv;
	puts_("Function implementation failed \n");
	if (0)
		puts_(*arr_args);
	return (0);
}
