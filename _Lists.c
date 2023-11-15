#include "_Shell.h"

/**
 * node_add - adds node at the beginning of a list
 * @_head: pointer to the list
 * @ptr_string: field for string
 * @_data: index of used node
 * Return: final list
 */

str_lists_t *node_add(str_lists_t **_head, const char *ptr_string, int _data)
{
	str_lists_t *n_head;

	if (!_head)
	return (NULL);
	n_head = malloc(sizeof(str_lists_t));
	if (!n_head)
	return (NULL);
	mem_set((void *)n_head, 0, sizeof(str_lists_t));
	n_head->_data = _data;
	if (ptr_string)
	{
		n_head->ptr_string = str_up(ptr_string);
		if (!n_head->ptr_string)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->_next = *_head;
	*_head = n_head;
	return (n_head);
}

/**
 * node_add_end - adds node at end of a linked list
 * @_head: pointer to the list
 * @ptr_string: field for string
 * @_data: node index used
 * Return: final list
 */

str_lists_t *node_add_end(str_lists_t **_head, const char *ptr_string, int _data)
{
	str_lists_t *new_node, *node_0;

	if (!_head)
	return (NULL);

	node_0 = *_head;
	new_node = malloc(sizeof(str_lists_t));
	if (!new_node)
	return (NULL);
	mem_set((void *)new_node, 0, sizeof(str_lists_t));
	new_node->_data = _data;
	if (ptr_string)
	{
		new_node->ptr_string = str_up(ptr_string);
		if (!new_node->ptr_string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node_0)
	{
		while (node_0->_next)
		node_0 = node_0->_next;
		node_0->_next = new_node;
	}
	else
	*_head = new_node;
	return (new_node);
}

/**
 * p_str_list - outputs ptr_string element of the list
 * @h_d: pointer to the list
 * Return: final list
 */

size_t p_str_list(const str_lists_t *h_d)
{
	size_t x = 0;

	while (h_d)
	{
		puts_(h_d->ptr_string ? h_d->ptr_string : "(Nil)");
		puts_("\n");
		h_d = h_d->_next;
		x++;
	}
	return (x);
}

/**
 * del_node_indx - removes node at index
 * @_head: pointer to the string
 * @indx: position - 1 to delete from
 * Return: 0 on failure, 1 on success
 */

int del_node_indx(str_lists_t **_head, unsigned int indx)
{
	str_lists_t *node_0, *p_node;
	unsigned int x = 0;

	if (!_head || !*_head)
	return (0);

	if (!indx)
	{
		node_0 = *_head;
		*_head = (*_head)->_next;
		free(node_0->ptr_string);
		free(node_0);
		return (1);
	}
	node_0 = *_head;
	while (node_0)
	{
		if (x == indx)
		{
			p_node->_next = node_0->_next;
			free(node_0->ptr_string);
			free(node_0);
			return (1);
		}
	x++;
	p_node = node_0;
	node_0 = node_0->_next;
	}
	return (0);
}

/**
 * _free_l - used to free the nodes in the list
 * @h_ptr: pointer to the linked list
 * Return: no return value
 */

void _free_l(str_lists_t **h_ptr)
{
	str_lists_t *node_0, *x_node, *_head;

	if (!h_ptr || !*h_ptr)
	return;
	_head = *h_ptr;
	node_0 = _head;
	while (node_0)
	{
		x_node = node_0->_next;
		free(node_0->ptr_string);
		free(node_0);
		node_0 = x_node;
	}
	*h_ptr = NULL;
}
