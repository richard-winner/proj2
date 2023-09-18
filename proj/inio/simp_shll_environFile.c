#include "shell.h"

/**
 * _simp_shll_myenv - the function here prints the current environment
 * @info: Structure containing potential arguments
 * Used to maintain constant function prototype.
 * Return: Always return 0
 */
int _simp_shll_myenv(info_t *info)
{
	simp_shll_print_list_str(info->env);
	return (0);
}

/**
 * _simp_shll_getenv - function here gets the value of an environ variable
 * @info: this is the structure containing potential arguments
 * Used to maintain
 * @name: env var name
 * Return: the exact value
 */
char *_simp_shll_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = simp_shll_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _simp_shll_mysetenv - this function initialize a new environment variable
 * or modify an existing one
 * @info: Structure containing potential arguments
 * Used to maintain constant function prototype.
 *  Return: Always return 0
 */
int _simp_shll_mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_simp_shll_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_simp_shll_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _simp_shll_myunsetenv - this function removes an environment variable
 * @info: this is the structure containing potential arguments
 * Used to maintain constant function prototype
 * Return: Always return 0
 */
int _simp_shll_myunsetenv(info_t *info)
{
	int v;

	if (info->argc == 1)
	{
		_simp_shll_eputs("Too few arguements.\n");
		return (1);
	}
	for (v = 1; v <= info->argc; v++)
		_simp_shll_unsetenv(info, info->argv[v]);

	return (0);
}

/**
 * simp_shll_populate_env_list - the function here populates env linked list
 * @info: this is the structure containing potential arguments
 * Used to maintain constant function prototype.
 * Return: Always return 0
 */
int simp_shll_populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t v;

	for (v = 0; environ[v]; v++)
		simp_shll_add_node_end(&node, environ[v], 0);
	info->env = node;
	return (0);
}
