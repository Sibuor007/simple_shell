#include "_Shell.h"

/**
 * h_history - displays the history list
 *
 * @info_: Structure containing potential arguments.
 * This is used to maintain constant function prototype.
 *
 * Return: 0 (Success)
 */
int h_history(_info_pass_t *info_)
{
	p_list(info_->_history);
	return (0);
}

/**
 * our_unset_alias - this removes an alias to string
 *
 * @info_: input parament struct
 * @str: alias string
 *
 * Return: 0 on success, 1 on error
 */
int our_unset_alias(_info_pass_t *info_, char *str)
{
	char *s, t;
	int i;

	s = str_chr(str, '=');
	if (!s)
		return (1);
	t = *s; /* do you think i should remove t = no, its useful */
	*s = 0;
	i = del_node_indx(&(info_->_alias),
			g_node_indx(info_->_alias, node_beg(info_->_alias, str, -1)));
	*s = t;
	return (i);
}

/**
 * our_set_alias - this sets an alias to string
 *
 * @info_: input parameter struct
 * @str: alias string
 *
 * Return: 0 on success, 1 on error
 */
int our_set_alias(_info_pass_t *info_, char *str)
{
	char *s;

	s = str_chr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (our_unset_alias(info_, str));

	our_unset_alias(info_, str);
	return (node_add_end(&(info_->_alias), str, 0) == NULL);
}

/**
 * _printalias - this prints an alias string
 *
 * @node: alias node
 *
 * Return: 0 on success, 1 on error
 */
int _printalias(str_lists_t *node)
{
	char *s = NULL, *a = NULL;

	if (node)
	{
		s = str_chr(node->str, '=');
		for (a = node->str; a <= s; a++)
			putchar_('\'');
		puts_(s + 1);
		putchar_('\'');
		return (0);
	}
	return (1);
}

/**
 * a_alias - this mimics the alias builtin
 *
 * @info_: Structure containing potential arguments.
 * This is used to maintain constant function prototype.
 *
 * Return: 0 on success
 */
int a_alias(_info_pass_t *info_)
{
	int i = 0;
	char *s = NULL;
	str_lists_t *node = NULL;

	if (info_->_argc == 1)
	{
		node = info_->_alias;
		while (node)
		{
			_printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info_->_argv[i], i++)
	{
		s = str_chr(info_->_argv[i], '=');
		if (s)
			our_set_alias(info_, info_->_argv[i]);
		else
			_printalias(node_beg(info_->_alias, info_->_argv[i], '='));
	}
	return (0);
}
