#include "shell.h"

/**
 * simp_shll_list_len - Length of linked list is determined
 * @h: First node Pointer
 * Return: list size
 */

size_t simp_shll_list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * simp_shll_get_node_index - Index of node is given
 * @node: Node pointer
 * @head: List head pointer
 * Return: -1 or index of node
 */


ssize_t simp_shll_get_node_index(list_t *head, list_t *node)
{
	size_t r = 0;

	while (head)
	{
		if (head == node)
			return (r);
		head = head->next;
		r++;
	}
	return (-1);
}

/**
 * simp_shll_list_to_strings - Array of strings of the list->str is retured.
 * @head: First node Pointer
 * Return: str array
 */

char **simp_shll_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = simp_shll_list_len(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_simp_shll_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _simp_shll_strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}

/**
 * simp_shll_print_list - All elements of a list_t linked lst are Printed
 * @h: First node pointer
 * Return: List size
 */

size_t simp_shll_print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_simp_shll_puts(simp_shll_convert_number(h->num, 10, 0));
		_simp_shll_putchar(':');
		_simp_shll_putchar(' ');
		_simp_shll_puts(h->str ? h->str : "(nil)");
		_simp_shll_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * simp_shll_node_starts_with - Node whose string starts with prefix is Retured
 * @node: List head pointer
 * @c: Next char prefix to be match
 * @prefix: str to be matched
 * Return: Node match or NULL
 */

list_t *simp_shll_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = simp_shll_starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}