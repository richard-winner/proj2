#include "shell.h"

/**
 * simp_shll_get_environ - function returns the string array copy of our environ
 * @info: this is the structure containing potential arguments
 * Used to maintain constant function prototype.
 * Return: Always return 0
 */
char **simp_shll_get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = simp_shll_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _simp_shll_unsetenv - this removes an environment variable
 * @info: this is the structure containing potential arguments
 * Used to maintain constant function prototype
 * @var: the string env var property
 * Return: return 1 on delete, else 0 otherwise
 */
int _simp_shll_unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t v = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = simp_shll_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = simp_shll_delete_node_at_index(&(info->env), v);
			v = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		v++;
	}
	return (info->env_changed);
}

/**
 * _simp_shll_setenv - this initialize a new environment variable
 * or modify an existing one
 * @info: this is structure containing potential arguments
 * Used to maintain constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always return 0
 */
int _simp_shll_setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_simp_shll_strlen(var) + _simp_shll_strlen(value) + 2);
	if (!buf)
		return (1);
	_simp_shll_strcpy(buf, var);
	_simp_shll_strcat(buf, "=");
	_simp_shll_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = simp_shll_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	simp_shll_add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}