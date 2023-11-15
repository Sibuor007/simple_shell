#include "_Shell.h"

/**
 * len_list - this determines the length of a linked list
 *
 * @h: first node pointer
 *
 * Return: list size
 */
size_t len_list(const str_lists_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
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
	str_lists_t *node = head;
	size_t i = len_list(h), j;
	char **str;
	char *s;

	if (!head || !i)
		return (NULL);
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(str_len(node->s) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(str[j]);
			free(str);
			return (NULL);
		}
		s = str_cpy(s, node->s);
		str[i] = s;
	}
	str[i] = NULL;
	return (str);
}

/**
 * p_list - prints all the elements of a list_t linked list
 *
 * @h: first node pointer
 *
 * Return: list size
 */
size_t p_list(const str_lists_t *h)
{
	size_t i = 0;

	while (h)
	{
		puts_(convert_num(h->n, 10, 0));
		putchar_(':');
		putchar_(' ');
		puts_(h->str ? h->str : "(nil)");
		puts_("\n");
		h = h->next;
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
		mp = _start(head->str, prefix);
		if (mp && ((next_c == -1) || (*mp == c)))
			return (head);
		head = head->next;
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
		head = head->next;
		i++;
	}
	return (-1);
}
