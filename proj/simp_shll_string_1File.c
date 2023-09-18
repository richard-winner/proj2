#include "shell.h"

/**
 * _simp_shll_strcpy - this copies a string
 * @src: source
 * @dest: destination
 * Return: points to the destination
 */

char *_simp_shll_strcpy(char *dest, char *src)
{
	int t = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[t])
	{
		dest[t] = src[t];
		t++;
	}
	dest[t] = 0;
	return (dest);
}

/**
 * _simp_shll_puts - this prints an input string
 * @str: string to be printed
 * Return: NULL
 */

void _simp_shll_puts(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_simp_shll_putchar(str[n]);
		n++;
	}
}

/**
 * _simp_shll_putchar - writes the char c to stdout
 * @c: character to be printed
 * Return: returns 1 on success and returns -1 on error
 */

int _simp_shll_putchar(char c)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(1, buf, m);
		m = 0;
	}
	if (c != BUF_FLUSH)
		buf[m++] = c;
	return (1);
}

/**
 * _simp_shll_strdup - this duplicates a string
 * @str: string to be duplicated
 * Return: points to the duplicated string
 */

char *_simp_shll_strdup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}
