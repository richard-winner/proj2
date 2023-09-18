#include "shell.h"

/**
 * _simp_shll_myexit - the function here exits the shell
 * @info: this is the structure containing potential arguments
 *  Used to maintain
 * constant function prototype
 * Return: the exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _simp_shll_myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _simp_shll_erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			simp_shll_print_error(info, "Illegal number: ");
			_simp_shll_eputs(info->argv[1]);
			_simp_shll_eputchar('\n');
			return (1);
		}
		info->err_num = _simp_shll_erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _simp_shll_mycd - the function changes the current directory of the process
 * @info: Structure containing potential arguments
 * Used to maintain
 * constant function prototype
 * Return: Always return 0
 */
int _simp_shll_mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_simp_shll_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _simp_shll_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _simp_shll_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_simp_shll_strcmp(info->argv[1], "-") == 0)
	{
		if (!_simp_shll_getenv(info, "OLDPWD="))
		{
			_simp_shll_puts(s);
			_simp_shll_putchar('\n');
			return (1);
		}
		_simp_shll_puts(_simp_shll_getenv(info, "OLDPWD=")), _simp_shll_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _simp_shll_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		simp_shll_print_error(info, "can't cd to ");
		_simp_shll_eputs(info->argv[1]), _simp_shll_eputchar('\n');
	}
	else
	{
		_simp_shll_setenv(info, "OLDPWD", _simp_shll_getenv(info, "PWD="));
		_simp_shll_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _simp_shll_myhelp - function here changes the current directory of the process
 * @info: this is the structure containing potential arguments
 *  Used to maintain
 * constant function prototype
 * Return: Always return 0
 */
int _simp_shll_myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_simp_shll_puts("help call works. Function not yet implemented \n");
	if (0)
		_simp_shll_puts(*arg_array);
	return (0);
}
