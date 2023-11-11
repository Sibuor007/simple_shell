#include "_Shell.h"

/**
 * get_list_length - this determines the length of a linked list
 *
 * @h: first node pointer
 *
 * Return: list size
 */
size_t get_list_length(const list_t *h)
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
 * get_list_strings - this returns an array of strings of the list->str
 *
 * @head: first node pointer
 *
 * Return: array of strings
 */
char **get_list_strings(list_t *head)
{
	list_t *node = head;
	size_t i = get_list_length(h), j;
	char **str;
	char *s;

	if (!head || !i)
		return (NULL);
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		s = malloc(_strlen(node->s) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(str[j]);
			free(str);
			return (NULL);
		}
		s = _strcpy(s, node->s);
		str[i] = s;
	}
	str[i] = NULL;
	return (str);
}

/**
 * print_linked_list - prints all the elements of a list_t linked list
 *
 * @h: first node pointer
 *
 * Return: list size
 */
size_t print_linked_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_eputs(convert_number(h->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_eputs(h->str ? h->str : "(nil)");
		_eputs("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * find_node_with_prefix - returns the node whose string starts with a prefix
 *
 * @head: pointer to list head
 * @prefix: string to match
 * @next_c: the next character after prefix
 *
 * Return: matching node or null
 */
list_t *find_node_with_prefix(list_t *head, char *prefix, char next_c)
{
	char *mp = NULL;

	while (head)
	{
		mp = starts_with(head->str, prefix);
		if (mp && ((next_c == -1) || (*mp == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * find_node_position - this finds the position of a node in the list
 *
 * @head: pointer to list head
 * @n: pointer to the node
 *
 * Return: position of node or -1
 */
size_t find_node_position(list_t *head, list_t *n)
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
