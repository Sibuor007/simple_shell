#include "_Shell.h"

/**
 * g_environ - this will return the string array copy of environment
 * @info_: a structure that has arguments
 * Return: 0 always
 */

char **g_environ(_info_pass_t *info_)
{
	if (!info_->environ || info_->change_env_rn)
	{
		info_->environ =  str_list(info_->_env_copy);
		info_->change_env_rn = 0;
	}

	return (info_->environ);
}

/**
 * unset_env - Remove an environment variable
 * @info_: a structure that has arguments
 * Return: 0 on failure, 1 on success
 * @var_: the string in question
 */

int unset_env(_info_pass_t *info_, char *var_)
{
	str_lists_t *_node = info_->_env_copy;
	size_t x = 0;
	char *ptr;

	if (!_node || !var_)
	return (0);

	while (_node)
	{
		ptr = _start(_node->ptr_string, var_);
		if (ptr && *ptr == '=')
		{
			info_->change_env_rn =  del_node_indx(&(info_->_env_copy), x);
			x = 0;
			_node = info_->_env_copy;
			continue;
		}
		_node = _node->_next;
		x++;
	}
	return (info_->change_env_rn);
}

/**
 * set_env - for modifying or initializing an environment var
 * @info_: a structure with arguments
 * @var_: string property
 * @value_: the string _env_copy var_ value_
 * Return: 0
 */

int set_env(_info_pass_t *info_, char *var_, char *value_)
{
	char *buff_ = NULL;
	str_lists_t *_node;
	char *ptr;

	if (!var_ || !value_)
		return (0);

	buff_ = malloc(str_len(var_) + str_len(value_) + 2);
	if (!buff_)
		return (1);
	str_cpy(buff_, var_);
	str_cat(buff_, "=");
	str_cat(buff_, value_);
	_node = info_->_env_copy;
	while (_node)
	{
		ptr = _start(_node->ptr_string, var_);
		if (ptr && *ptr == '=')
		{
			free(_node->ptr_string);
			_node->ptr_string = buff_;
			info_->change_env_rn = 1;
			return (0);
		}
		_node = _node->_next;
	}
	node_add_end(&(info_->_env_copy), buff_, 0);
	free(buff_);
	info_->change_env_rn = 1;
	return (0);
}
