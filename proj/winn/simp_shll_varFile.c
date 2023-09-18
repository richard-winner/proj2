#include "shell.h"

/**
 * simp_shll_replace_string - replaces str
 * @old: address of old str
 * @new: new str
 * Return: returns 1 if replaced, otherwise returns 0
 */

int simp_shll_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * simp_shll_is_chain - test to check if current char in buffer is a chain delimeter
 * @p: current position of address in buff
 * @buf: char buffer
 * @info: struct parameter
 * Return: returns 1 if chain delimeter, otherwise it returns 0
 */

int simp_shll_is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * simp_shll_replace_alias - in the tokenized string it replaces an alias
 * @info: struct parameter
 * Return: returns 1 if replaced, otherwise returns 0
 */

int simp_shll_replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = simp_shll_node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _simp_shll_strchr(node->str, '=');
		if (!p)
			return (0);
		p = _simp_shll_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * simp_shll_check_chain - test to check if we should continue
 * chaining based on the last status
 * @len: length of buff
 * @p: current position of address in buff
 * @buf: char buffer
 * @i: starting position in buf
 * @info: struct parameter
 * Return: NULL
 */

void simp_shll_check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * simp_shll_replace_vars - in the tokenized string it replaces vars
 * @info: struct parameter
 * Return: returns 1 if replaced, otherwise returns 0
 */

int simp_shll_replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_simp_shll_strcmp(info->argv[i], "$?"))
		{
			simp_shll_replace_string(&(info->argv[i]),
					_simp_shll_strdup(simp_shll_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_simp_shll_strcmp(info->argv[i], "$$"))
		{
			simp_shll_replace_string(&(info->argv[i]),
					_simp_shll_strdup(simp_shll_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = simp_shll_node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			simp_shll_replace_string(&(info->argv[i]),
					_simp_shll_strdup(_simp_shll_strchr(node->str, '=') + 1));
			continue;
		}
		simp_shll_replace_string(&info->argv[i], _simp_shll_strdup(""));

	}
	return (0);
}