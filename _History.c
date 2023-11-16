#include "_Shell.h"

/**
 * g_history_f - function that fetches file _history
 * @info_: item in the structure
 * Return: string that has the file _history
 */  

char *g_history_f(_info_pass_t *info_)
{
	char *_buff, *dir_f;

	dir_f = get_env(info_, "HOME: ");
	if (!dir_f)
	return (NULL);
	_buff = malloc(sizeof(char) * (str_len(dir_f) + str_len(FILE_HISTORY) + 2));
	if (!_buff)
	return (NULL);
	_buff[0] = 0;
	str_cpy(_buff, dir_f);
	str_cat(_buff, "/");
	str_cat(_buff, FILE_HISTORY);
	return (_buff);
}

/**
 * history_write - function that appends to or creates a file
 * @info_: item in the structure
 * Return: -1 on failure, 1 otherwise
 */
int history_write(_info_pass_t *info_)
{
	ssize_t file_;
	char *f_name = g_history_f(info_);
	str_lists_t *node_n = NULL;

	if (!f_name)
	return (-1);

	file_ = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (file_ == -1)
	return (-1);
	for (node_n = info_->_history; node_n; node_n = node_n->_next)
	{
		put_def_f(node_n->ptr_string, file_);
		puts_def_f("\n", file_);
	}
	puts_def_f(FLUSH_BUFFER, file_);
	close(file_);
	return (1);
}

/**
 * history_read - function to read history from a file
 * @info_: item in the defined structure
 * Return: 0 otherwise, history on success
 */

int history_read(_info_pass_t *info_)
{
	int x, var_0 = 0, count_line = 0;
	ssize_t file_, rd_len, f_size = 0;
	struct stat start;
	char *_buff = NULL, *f_name = g_history_f(info_);

	if (!f_name)
	return (0);

	file_ = open(f_name, O_RDONLY);
	free(f_name);
	if (file_ == -1)
	return (0);
	if (!fstat(file_, &start))
	f_size = start.st_size;
	if (f_size < 2)
	return (0);
	_buff = malloc(sizeof(char) * (f_size + 1));
	if (!_buff)
	return (0);
	rd_len = read(file_, _buff, f_size);
	_buff[f_size] = 0;
	if (rd_len <= 0)
	return (free(_buff), 0);
	close(file_);
	for (x = 0; x < f_size; x++)
	if (_buff[x] == '\n')
	{
		_buff[x] = 0;
		history_built_l(info_, _buff + var_0, count_line++);
		var_0 = x + 1;
	}
	if (var_0 != x)
	history_built_l(info_, _buff + var_0, count_line++);
	free(_buff);
	info_->count_history = count_line;
	while (info_->count_history-- >= MAX_HISTORY)
	del_node_indx(&(info_->_history), 0);
	history_recall(info_);
	return (info_->count_history);
}

/**
 * history_built_l - allows entry to history linked list
 * @info_: item in a structure
 * @_buff: the buffer
 * @count_line: the count of history
 * Return: 0 always
 */

int history_built_l(_info_pass_t *info_, char *_buff, int count_line)
{
	str_lists_t *node_n = NULL;

	if (info_->_history)
	node_n = info_->_history;
	node_add_end(&node_n, _buff, count_line);

	if (!info_->_history)
	info_->_history = node_n;
	return (0);
}

/**
 * history_recall - after modification, it renumbers the linked list
 * @info_: structure that contains arguments
 * Return: the updated history count
 */

int history_recall(_info_pass_t *info_)
{
	str_lists_t *node_n = info_->_history;
	int x = 0;

	while (node_n)
	{
		node_n->_data = x++;
		node_n = node_n->_next;
	}
	return (info_->count_history = x);
}
