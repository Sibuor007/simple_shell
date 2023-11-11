#include "_Shell.h"

/**
 * add_n - this adds a node to the start of the list
 *
 * @head: pointer address to head node
 * @str: node string field
 * @n: node index used by history
 *
 * Return: list size
 */
list_t *add_n(list_t **head, const char *str, int n)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t))
		new->n = n;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_n_end - this adds a node to the end of the list
 *
 * @head: pointer address to head node
 * @str: node string field
 * @n: node index used by history
 *
 * Return: list size
 */
list_t *add_n_end(list_t **head, const char *str, int n)
{
	list_t *new_n, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_n = malloc(sizeof(list_t));
	if (!new_n)
		return (NULL);
	_memset((void *)new_n, 0, sizeof(list_t));
	new_n->n = n;
	if (str)
	{
		new_n->str = _strdup(str);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_n;
	}
	else
		*head = new_n;
	return (new_n);
}

/**
 * print_string_list - this prints the string elements of a list_t linked list
 *
 * @h: first node pointer
 *
 * Return: list size
 */
size_t print_string_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_eputs(h->str ? h->str : "(nil)");
		_eputs("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_position - this deletes node at given position
 *
 * @head: pointer address to first node
 * @position: position of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_position(list_t **head, unsigned int position)
{
	list_t *node, *previous_n;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!position)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == position)
		{
			previous_n->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		previous_n = node;
		node = node->next;
	}
	return (0);
}

/**
 * release_list - this frees all nodes of a list
 *
 * @head: pointer address of head node
 *
 * Return: void
 */
void release_list(list_t **head)
{
	list_t *node, *next_n, *head;

	if (!head || !*head)
		return;
	head = *head;
	node = head;
	while (node)
	{
		next_n = node->next;
		free(node->str);
		free(node);
		node = next_n;
	}
	*head = NULL;
}
