#include "shell.h"

/**
 * simp_shll_hsh - the main shell loop
 * @av: the main() argument vector
 * @info: returns info struct and the parameter
 * Return: returns 0 on success and 1 on error
 */

int simp_shll_hsh(info_t *info, char **av)
{
	ssize_t v = 0;
	int builtin_ret = 0;

	while (v != -1 && builtin_ret != -2)
	{
		simp_shll_clear_info(info);
		if (simp_shll_interactive(info))
			_simp_shll_puts("$ ");
		_simp_shll_eputchar(BUF_FLUSH);
		v = simp_shll_get_input(info);
		if (v != -1)
		{
			simp_shll_set_info(info, av);
			builtin_ret = simp_shll_find_builtin(info);
			if (builtin_ret == -1)
				simp_shll_find_cmd(info);
		}
		else if (simp_shll_interactive(info))
			_simp_shll_putchar('\n');
		simp_shll_free_info(info, 0);
	}
	simp_shll_write_history(info);
	simp_shll_free_info(info, 1);
	if (!simp_shll_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * simp_shll_find_builtin - fuction finds a built-in command in code
 * @info: returns info struct and the parameter
 * RETURNS:
 * Return: f built-in is not found in code,
 * returns 0 if built-in is executed successfully,
 * returns 1 if built-in is found but failed,
 * and returns 2 if built-in signals an exit() from code
 */

int simp_shll_find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _simp_shll_myexit},
		{"env", _simp_shll_myenv},
		{"help", _simp_shll_myhelp},
		{"history", _simp_shll_myhistory},
		{"setenv", _simp_shll_mysetenv},
		{"unsetenv", _simp_shll_myunsetenv},
		{"cd", _simp_shll_mycd},
		{"alias", _simp_shll_myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_simp_shll_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * simp_shll_find_cmd - finds a command in the PATH
 * @info: returns info struct and the parameter
 * Return: NULL
 */

void simp_shll_find_cmd(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!simp_shll_is_delim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = simp_shll_find_path(info, _simp_shll_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		simp_shll_fork_cmd(info);
	}
	else
	{
		if ((simp_shll_interactive(info) || _simp_shll_getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && simp_shll_is_cmd(info, info->argv[0]))
			simp_shll_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			simp_shll_print_error(info, "not found\n");
		}
	}
}

/**
 * simp_shll_fork_cmd - forks an execution thread to run command
 * @info: returns info struct and the parameter
 * Return: NULL
 */

void simp_shll_fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, simp_shll_get_environ(info)) == -1)
		{
			simp_shll_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				simp_shll_print_error(info, "Permission denied\n");
		}
	}
}