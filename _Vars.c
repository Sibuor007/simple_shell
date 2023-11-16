#include "_Shell.h"

/**
 * _chain - checks for occurence of chain delimeter in buffer
 * @info_: structure element
 * @buff_: buffer for character
 * @ptr: pointer to the buffer
 * Return: 1 on success, 0 otherwise
 */

int _chain(_info_pass_t *info_, char *buff_, size_t *ptr)
{
	size_t y = *ptr;

	if (buff_[y] == '|' && buff_[y + 1] == '|')
	{
		buff_[y] = 0;
		y++;
		info_->type_cmd_buffer = OR_COMMAND;
	}
	else if (buff_[y] == '&' && buff_[y + 1] == '&')
	{
		buff_[y] = 0;
		y++;
		info_->type_cmd_buffer = AND_COMMAND;
	}
	else if (buff_[y] == ';')
	{
		buff_[y] = 0;
		info_->type_cmd_buffer = CHAIN_COMMAND;
	}
	else
	return (0);
	*ptr = y;
	return (1);
}

/**
 * _chain_check - checks for chaining w.r.t prev status
 * @info_: item in structure
 * @buff_: buffer for character
 * @ptr: pointer to the buff_
 * @x: start of the buff_
 * @length: length of buff_
 * Return: no return value
 */

void _chain_check(_info_pass_t *info_, char *buff_, size_t *ptr, size_t x, size_t length)
{
	size_t y = *ptr;

	if (info_->type_cmd_buffer == AND_COMMAND)
	{
		if (info_->_status)
		{
			buff_[x] = 0;
			y = length;
		}
	}
	if (info_->type_cmd_buffer == OR_COMMAND)
	{
		if (!info_->_status)
		{
			buff_[x] = 0;
			y = length;
		}
	}

	*ptr = y;
}

/**
 * _alias_replace - substitute an _alias in string
 * @info_: item in structure
 * Return: 1 on success, 0 otherwise
 */

int _alias_replace(_info_pass_t *info_)
{
	int x;
	str_lists_t *node_;
	char *ptr;

	for (x = 0; x < 10; x++)
	{
		node_ = node_beg(info_->_alias, info_->_argv[0], '=');
		if (!node_)
		return (0);
		free(info_->_argv[0]);
		ptr = str_chr(node_->ptr_string, '=');
		if (!ptr)
		return (0);
		ptr = str_up(ptr + 1);
		if (!ptr)
		return (0);
		info_->_argv[0] = ptr;
	}
	return (1);
}

/**
 * _vars_replace - in tokenized string,
 * the function replaces vars
 * @info_: the parameter struct
 * Return: 1 on success, 0 otherwise
 */

int _vars_replace(_info_pass_t *info_)
{
	int x = 0;
	str_lists_t *node_;

	for (x = 0; info_->_argv[x]; x++)
	{
		if (info_->_argv[x][0] != '$' || !info_->_argv[x][1])
		continue;

		if (!str_cmp(info_->_argv[x], "$?"))
		{
			_str_replace(&(info_->_argv[x]),
			str_up(convert_num(info_->_status, 10, 0)));
			continue;
		}
		if (!str_cmp(info_->_argv[x], "$$"))
		{
			_str_replace(&(info_->_argv[x]),
			str_up(convert_num(getpid(), 10, 0)));
			continue;
		}
		node_ = node_beg(info_->_env_copy, &info_->_argv[x][1], '=');
		if (node_)
		{
			_str_replace(&(info_->_argv[x]),
			str_up((str_chr(node_->ptr_string, '=') + 1));
			continue;
		}
			_str_replace(&info_->_argv[x], str_up(""));

	}
	return (0);
}

/**
 * _str_replace - function that replaces a string
 * @prev_: pointer to the previous string
 * @_new: pointer to the new string
 * Return: 1 on success, 0 otherwise
 */

int _str_replace(char **prev_, char *_new)
{
	free(*prev_);
	*prev_ = _new;
	return (1);
}
