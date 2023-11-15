#include "_Shell.h"

/**
 * free_f - frees a pointer and sets it to NULL
 *
 * @ptr: address of the pointer
 *
 * Return: 1 if freed, 0 if the pointer is already NULL
 */
int free_f(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
