#include "_Shell.h"

/**
 * info_clear - a function that initializes structure
 * @info_: structure that contains arguments
 */

void info_clear(_info_pass_t *info_)
{
	info_->_args = NULL;
	info_->_argv = NULL;
	info_->_str_path = NULL;
	info_->_argc = 0;
}

/**
 * info_set - function that initializes struct
 * @info_: structure that contains arguments
 * @a_v: Argument vector
 */

void info_set(_info_pass_t *info_, char **a_v)
{
	int x = 0;

	info_->_filename = a_v[0];
	if (info_->_args)
	{
		info_->_argv = _str_tow(info_->_args, " \t");
		if (!info_->_argv)
		{

			info_->_argv = malloc(sizeof(char *) * 2);
			if (info_->_argv)
			{
				info_->_argv[0] = str_up(info_->_args);
				info_->_argv[1] = NULL;
			}
		}
		for (x = 0; info_->_argv && info_->_argv[x]; x++)
		;
		info_->_argc = x;

		_alias_replace(info_);
		_vars_replace(info_);
	}
}

/**
 * info_free - used to free structure fields
 * @info_: structure that has argument
 * @field_: true for success
 */

void info_free(_info_pass_t *info_, int field_)
{
	_free(info_->_argv);
	info->_argv = NULL;
	info_->_str_path = NULL;
	if (field_)
	{
		if (!info_->buffer_cmd)
		free(info_->_args);
		if (info_->_env_copy)
		_free_l(&(info_->_env_copy));
		if (info_->_history)
		_free_l(&(info_->_history));
		if (info_->_alias)
		_free_l(&(info_->_alias));
		_free(info_->dl_env_rn);
		info_->dl_env_rn = NULL;
		free_f((void **)info_->buffer_cmd);
		if (info_->_input_read > 2)
		close(info_->_input_read);
		putchar_(FLUSH_BUFFER);
	}
}
