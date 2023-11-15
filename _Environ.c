#include "_Shell.h"

/**
 * e_env - function that prints the environment
 * @info_: a potential structure with arguments
 * Return: 0
 */

int e_env(_info_pass_t *info_)
{
	p_str_list(info_->_env_copy);
	return (0);
}

/**
 * get_env - used to get the value of variable
 * @info_: a structure that contains arguments
 * @var_: name for the enviornment variable
 * Return: the value
 */

char *get_env(_info_pass_t *info_, const char *var_)
{
	str_lists_t *n_node = info_->_env_copy;
	char *ptr;

	while (n_node)
	{
		ptr = _start(n_node->ptr_string, var_);
		if (ptr && *ptr)
		return (ptr);
		n_node = n_node->_next;
	}
	return (NULL);
}

/**
 * s_setenv - to initialize or modify a variable
 * @info_: a structure that has arguments
 *  Return: 0
 */

int s_setenv(_info_pass_t *info_)
{
	if (info_->_argc != 3)
	{
		puts_err("Invalid no. of args\n");
		return (1);
	}
	if (set_env(info_, info_->_argv[1], info_->_argv[2]))
		return (0);
	return (1);
}

/**
 * u_unsetenv - used to remove a variable
 * @info_: a structure that has arguments
 *  Return: 0
 */

int u_unsetenv(_info_pass_t *info_)
{
	int x;

	if (info_->_argc == 1)
	{
		puts_err("Few arguments.\n");
		return (1);
	}
	for (x = 1; x <= info_->_argc; x++)
	unset_env(info_, info_->_argv[x]);

	return (0);
}

/**
 * env_populate - function that populates the linked list
 * @info_: a structure that contains arguments
 * Return: 0
 */

int env_populate(_info_pass_t *info_)
{
	str_lists_t *n_node = NULL;
	size_t x;

	for (x = 0; dl_env_rn[x]; x++)
	node_add_end(&n_node, dl_env_rn[x], 0);
	info_->_env_copy = n_node;

	return (0);
}
