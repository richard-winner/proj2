#include "shell.h"

/**
 * _simp_shll_eputs - the function here prints input string
 * @str: this is the string to be printed
 * Return: nay
 */
void _simp_shll_eputs(char *str)
{
	int v = 0;

	if (!str)
		return;
	while (str[v] != '\0')
	{
		_simp_shll_eputchar(str[v]);
		v++;
	}
}

/**
 * _simp_shll_eputchar - function here writes the character c to stderr
 * @c: this is the character to print
 * Return: On success 1 On error, -1 is returned
 * and errno is set appropriately
 */
int _simp_shll_eputchar(char c)
{
	static int v;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(2, buf, v);
		v = 0;
	}
	if (c != BUF_FLUSH)
		buf[v++] = c;
	return (1);
}

/**
 * _simp_shll_putfd - this writes the character c to given fd
 * @c: this is the char to print
 * @fd: filedescriptor to write to
 * Return: On success 1 On error, -1 is returned
 * and errno is set appropriately.
 */
int _simp_shll_putfd(char c, int fd)
{
	static int v;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(fd, buf, v);
		v = 0;
	}
	if (c != BUF_FLUSH)
		buf[v++] = c;
	return (1);
}

/**
 * _simp_shll_putsfd - function here prints input string
 * @str: string to be printed
 * @fd: filedescriptor to write to
 * Return: the number of chars put
 */
int _simp_shll_putsfd(char *str, int fd)
{
	int v = 0;

	if (!str)
		return (0);
	while (*str)
	{
		v += _simp_shll_putfd(*str++, fd);
	}
	return (v);
}
