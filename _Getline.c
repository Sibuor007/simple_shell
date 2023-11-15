#include "shell.h"

/**
 * buff_input - buffers chained commands
 * @info_: element of structure
 * @buff_: pointer to buffer
 * @len_h: pointer to len_h
 * Return: bytes read
 */

ssize_t buff_input (_info_pass_t *info_, char **buff_, size_t *len_h)
{
	ssize_t n = 0;
	size_t len_p = 0;

	if (!*len_h)
	{
		free(*buff_);
		*buff_ = NULL;
		signal(SIGINT, in_handler);
		#if USE_GETLINE
		n = getline(buff_, &len_p, stdin);
		#else
		n = g_line(info_, buff_, &len_p);
		#endif
		if (n > 0)
		{
			if ((*buff_)[n - 1] == '\n')
			{
				(*buff_)[n - 1] = '\0';
				n--;
			}
			info_->flag_count = 1;
			rm_comments(*buff_);
			history_built_l(info_, *buff_, info_->count_history++);
			{
				*len_h = n;
				info_->buffer_cmd = buff_;
			}
		}
	}
	return (n);
}

/**
 * get_input - function that gets line
 * @info_: element of structure
 * Return: bytes read
 */

ssize_t g_input(_info_pass_t *info_)
{
	static char *buff_;
	static size_t i, j, len_h;
	ssize_t n = 0;
	char **buf_p = &(info_->_arg), *p_tr;

	putchar_(FLUSH_BUFFER);
	n = buff_input(info_, &buff_, &len_h);
	if (n == -1)
	return (-1);
	if (len_h)
	{
		j = i;
		p_tr = buff_ + i;

		_chain_check(info_, buff_, &j, i, len_h);
		while (j < len_h)
		{
			if (_chain(info_, buff_, &j))
			break;
			j++;
		}

		i = j + 1;
		if (i >= len_h)
		{
			i = len_h = 0;
			info_->type_cmd_buffer = NORMAL_COMMAND;
		}

		*buf_p = p_tr;
		return (str_len(p_tr));
	}

	*buf_p = buff_;
	return (n);
}

/**
 * read_buf - function that reads buffer
 * @info_: element of structure
 * @buff_: pointer to the buffer
 * @i: size
 *
 * Return: n
 */

ssize_t read_buf(_info_pass_t *info_, char *buff_, size_t *i)
{
	ssize_t n = 0;

	if (*i)
	return (0);
	n = read(info_->_input_read, buff_, BUFFER_SIZE_READ);
	if (n >= 0)
	*i = n;
	return (n);
}

/**
 * _getline - function to get line from standard input
 * @info_: item in the structure
 * @ptr_: pointer to the buffer
 * @length: size of buffer, if not null
 * Return: p_tr
 */

int g_line(_info_pass_t *info_, char **ptr_, size_t *length)
{
	static char buff_[BUFFER_SIZE_READ];
	static size_t i, len_h;
	size_t m;
	ssize_t n = 0, p_tr = 0;
	char *p_tr = NULL, *new_ptr = NULL, *ch;

	p_tr = *ptr_;
	if (p_tr && length)
	p_tr = *length;
	if (i == len_h)
	i = len_h = 0;

	n = read_buf(info_, buff_, &len_h);
	if (n == -1 || (n == 0 && len_h == 0))
	return (-1);

	ch = str_chr(buff_ + i, '\n');
	m = ch ? 1 + (unsigned int)(ch - buff_) : len_h;
	new_ptr = re_alloc(p_tr, p_tr, p_tr ? p_tr + m : m + 1);
	if (!new_ptr)
	return (p_tr ? free(p_tr), -1 : -1);

	if (p_tr)
	str_n_cat(new_ptr, buff_ + i, m - i);
	else
	str_n_cpy(new_ptr, buff_ + i, m - i + 1);

	p_tr += m - i;
	i = m;
	p_tr = new_ptr;

	if (length)
	*length = p_tr;
	*ptr_ = p_tr;
	return (p_tr);
}

/**
 * in_handler - function to blocks ctrl-C
 * @s_num: the signal number
 * Return: void
 */

void in_handler(__attribute__((unused))int s_num)
{
	puts_("\n");
	puts_("$ ");
	putchar_(FLUSH_BUFFER);
}
