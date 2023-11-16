#include "_Shell.h"

/**
 * mem_set - fills memory with a constant byte
 *
 * @dest: pointer to the memory area
 * @byte: byte to fill *s with
 * @num: the amount of bytes to fill
 *
 * Return: a pointer to the the memory area s
 */
char *mem_set(char *dest, char byte, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		dest[i] = byte;
	return (dest);
}

/**
 * _myfree - fress a string array
 *
 * @p: string array
 */
void _myfree(char **p)
{
	char **x = p;

	if (!p)
		return;

	while (*p)
		free(*p++);
	free(x);
}

/**
 * re_alloc - reallocates a block of memory
 *
 * @ptr: pointer to previous malloc'ated block
 * @prev_size: bytes size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *re_alloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *x;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	x = malloc(new_size);
	if (!x)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		x[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (x);
}
