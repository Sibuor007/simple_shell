#include "_Shell.h"

/**
 * len_list - this determines the length of a linked list
 *
 * @h_d: first node pointer
 *
 * Return: list size
 */
size_t len_list(const str_lists_t *h_d)
{
	size_t i = 0;

	while (h_d)
	{
		h_d = h_d->_next;
		i++;
	}
	return (i);
}

/**
 * str_list - this returns an array of strings of the list->str
 *
 * @head: first node pointer
 *
 * Return: array of strings
 */
char **str_list(str_lists_t *head)
{
	str_lists_t *node_ = head;
	size_t i = len_list(head), j;
	char **str;
	char *s;

	if (!head || !i)
		return (NULL);
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	for (i = 0; node_; node_ = node_->_next, i++)
	{
		s = malloc(str_len(node_->ptr_string) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(str[j]);
			free(str);
			return (NULL);
		}
		s = str_cpy(s, node_->ptr_string);
		str[i] = s;
	}
	str[i] = NULL;
	return (str);
}

/**
 * p_list - prints all the elements of a list_t linked list
 *
 * @h_d: first node pointer
 *
 * Return: list size
 */
size_t p_list(const str_lists_t *h_d)
{
	size_t i = 0;

	while (h_d)
	{
		puts_(convert_num(h_d->_data, 10, 0));
		putchar_(':');
		putchar_(' ');
		puts_(h_d->ptr_string ? h_d->ptr_string : "(nil)");
		puts_("\n");
		h_d = h_d->_next;
		i++;
	}
	return (i);
}

/**
 * node_beg - returns the node whose string begins with a prefix
 *
 * @head: pointer to list head
 * @prefix: string to match
 * @next_c: the next character after prefix
 *
 * Return: matching node or null
 */
str_lists_t *node_beg(str_lists_t *head, char *prefix, char next_c)
{
	char *mp = NULL;

	while (head)
	{
		mp = _start(head->ptr_string, prefix);
		if (mp && ((next_c == -1) || (*mp == next_c)))
			return (head);
		head = head->_next;
	}
	return (NULL);
}

/**
 * g_node_indx - this finds the position of a node in the list
 *
 * @head: pointer to list head
 * @n: pointer to the node
 *
 * Return: position of node or -1
 */
size_t g_node_indx(str_lists_t *head, str_lists_t *n)
{
	size_t i = 0;

	while (head)
	{
		if (head == n)
			return (i);
		head = head->_next;
		i++;
	}
	return (-1);
}
