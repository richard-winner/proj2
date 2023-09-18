#include "shell.h"

/**
 * simp_shll_bfree - When a pointer is freed NULLs its address
 * @ptr: Addess of ptr to be frred
 * Return: for freed 1, else 0
 */

int simp_shll_bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}