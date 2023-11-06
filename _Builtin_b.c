#include "_Shell.h"

/**
 * our_history - displays the history list
 *
 * @info: Structure containing potential arguments.
 * This is used to maintain constant function prototype.
 *
 * Return: 0 (Success)
 */
int our_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * our_unset_alias - this removes an alias to string
 *
 * @info: input parament struct
 * @str: alias string
 *
 * Return: 0 on success, 1 on error
 */
int our_unset_alias(info_t *info, char *str)
{
	char *s, t;
	int i;
	
	s = _strchr(str, '=');
	if (!s)
		return (1);
	t = *s; /* do you think i should remove t */
	*s = 0;
	i = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*s = t;
	return (i);
}

/**
 * our_set_alias - this sets an alias to string
 *
 * @info: input parameter struct
 * @str: alias string
 *
 * Return: 0 on success, 1 on error
 */
int our_set_alias(info_t *info, char *str)
{
	char *s;

	s = _strchr(str, '=');
	if (!s)
		return (1);
	if (!*++s)
		return (our_unset_alias(info, str));

	our_unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _printalias - this prints an alias string
 *
 * @node: alias node
 *
 * Return: 0 on success, 1 on error
 */
int _printalias(list_t *node)
{
	char *s = NULL, *a = NULL;

	if (node)
	{
		s = _strchr(node->str, '=');
		for (a = node-.str; a <= s; a++)
			_putchar('\'');
		_puts(s + 1);
		_putchar('\'); /* check this line */
		return (0);
	}
	return (1);
}

/**
 * our_alias - this mimics the alias builtin
 *
 * @info: Structure containing potential arguments.
 * This is used to maintain constant function prototype.
 *
 * Return: 0 on success
 */
int our_alias(info_t *info)
{
	int i = 0;
	char *s = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i], i++)
	{
		s = _strchr(info->argv[i], '=');
		if (s)
			our_set_alias(info, info->argv[i]);
		else
			_printalias(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
