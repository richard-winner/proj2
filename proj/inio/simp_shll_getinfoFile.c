#include "shell.h"

/**
 * simp_shll_clear_info - function here initializes info_t struct
 * @info: the struct address
 */
void simp_shll_clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * simp_shll_set_info - function initializes info_t struct
 * @av: the argument vector
 * @info: the struct address
 */
void simp_shll_set_info(info_t *info, char **av)
{
	int v = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = simp_shll_strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _simp_shll_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (v = 0; info->argv && info->argv[v]; v++)
			;
		info->argc = v;

		simp_shll_replace_alias(info);
		simp_shll_replace_vars(info);
	}
}

/**
 * simp_shll_free_info - this function frees info_t struct fields
 * @info: the struct address
 * @all: the true if freeing all fields
 */
void simp_shll_free_info(info_t *info, int all)
{
	simp_shll_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			simp_shll_free_list(&(info->env));
		if (info->history)
			simp_shll_free_list(&(info->history));
		if (info->alias)
			simp_shll_free_list(&(info->alias));
		simp_shll_ffree(info->environ);
			info->environ = NULL;
		simp_shll_bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_simp_shll_putchar(BUF_FLUSH);
	}
}