#include "_Shell.h"

/**
 * _h_shell - main shell loop
 * @info_: the parameter & return info_ struct
 * @arg_v: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */

int _h_shell(_info_pass_t *info_, char **arg_v)
{
	ssize_t m = 0;
	int blt_in_r = 0;

	while (m != -1 && blt_in_r != -2)
	{
		info_clear(info_);
		if (_i_active(info_))
		puts_("$ ");
		putchar_err(FLUSH_BUFFER);
		m = g_input(info_);
		if (m != -1)
		{
			info_set(info_, arg_v);
			blt_in_r = builtin_find(info_);
			if (blt_in_r == -1)
			command_find(info_);
		}
		else if (_i_active(info_))
		putchar_('\n');
		info_free(info_, 0);
	}
	history_write(info_);
	info_free(info_, 1);
	if (!_i_active(info_) && info_->_status)
	exit(info_->_status);
	if (blt_in_r == -2)
	{
		if (info_->_errno == -1)
		exit(info_->_status);
		exit(info_->_errno);
	}
	return (blt_in_r);
}

/**
 * builtin_find - used to find builtin cmd
 * @info_: element in structure
 * Return: multiple
 */

int builtin_find(_info_pass_t *info_)
{
		int x, blt_in_r = -1;
		builtin_b builtin_bl[] = {
		{"exit", _exit},
		{"env", e_env},
		{"help", _help},
		{"history", h_history},
		{"setenv", s_setenv},
		{"unsetenv", u_unsetenv},
		{"cd", _cd},
		{"alias", a_alias},
		{NULL, NULL}
	};

	for (x = 0; builtin_bl[x].flag_type; x++)
	if (str_cmp(info_->_argv[0], builtin_bl[x].flag_type) == 0)
	{
		info_->_counts_line++;
		blt_in_r = builtin_bl[x].def_f(info_);
		break;
	}
	return (blt_in_r);
}

/**
 * command_find - screens for cmd in PATH
 * @info_: element in structure
 * Return: No return value
 */

void command_find(_info_pass_t *info_)
{
	char *_str_path = NULL;
	int x, j;

	info_->_str_path = info_->_argv[0];
	if (info_->flag_count == 1)
	{
		info_->_counts_line++;
		info_->flag_count = 0;
	}
	for (x = 0, j = 0; info_->_args[x]; x++)
	if (!delim_(info_->_args[x], " \t\n"))
	j++;
	if (!j)
	return;

	_str_path = _path_find(info_, get_env(info_, "PATH: "), info_->_argv[0]);
	if (_str_path)
	{
		info_->_str_path = _str_path;
		command_fork(info_);
	}
	else
	{
		if ((_i_active(info_) || get_env(info_, "PATH: ")
		|| info_->_argv[0][0] == '/') && curr_cmd(info_, info_->_argv[0]))
		command_fork(info_);
		else if (*(info_->_args) != '\n')
		{
			info_->_status = 127;
			p_error(info_, "not available\n");
		}
	}
}

/**
 * command_fork - forks thread to run cmd
 * @info_: element in structure
 * Return: no return value
 */

void command_fork(_info_pass_t *info_)
{
	pid_t curr_pid;

	curr_pid = fork();
	if (curr_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (curr_pid == 0)
	{
		if (execve(info_->_str_path, info_->_argv, g_environ(info_)) == -1)
		{
			info_free(info_, 1);
			if (errno == EACCES)
			exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info_->_status));
		if (WIFEXITED(info_->_status))
		{
			info_->_status = WEXITSTATUS(info_->_status);
			if (info_->_status == 126)
			p_error(info_, "Permission Denied\n");
		}
	}
}
