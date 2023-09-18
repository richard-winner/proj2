#include "shell.h"

/**
 * _simp_shll_realloc - Block of memory reallocated
 * @ptr: pointer to previous malloc'ated block
 * @old_size: previous block byte size
 * @new_size: New block byte size
 * Return: ol'block named pointer
 */


void *_simp_shll_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}


/**
 * _simp_shll_memset - Memory filling with constant byte
 * @b: Fill *s with byte
 *  @s: Memory area pointer
 * @n: Amount of bytes to be filled
 * Return: Memory area pointer
 */

char *_simp_shll_memset(char *s, char b, unsigned int n)
{
	unsigned int u;

	for (u = 0; u < n; u++)
		s[u] = b;
	return (s);
}

/**
 * simp_shll_ffree - This frees a str of strs
 * @pp: str of strs
 */

void simp_shll_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}


