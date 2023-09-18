#include "shell.h"

/**
 * input_buf - function here buffers chained commands
 * @info: the parameter struct
 * @buf: the address of buffer
 * @len: the address of len var
 * Return:return bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t w = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, simp_shll_sigintHandler);
#if USE_GETLINE
		w = getline(buf, &len_p, stdin);
#else
		w = _simp_shll_getline(info, buf, &len_p);
#endif
		if (w > 0)
		{
			if ((*buf)[w - 1] == '\n')
			{
				(*buf)[w - 1] = '\0';
				w--;
			}
			info->linecount_flag = 1;
			simp_shll_remove_comments(*buf);
			simp_shll_build_history_list(info, *buf, info->histcount++);
			{
				*len = w;
				info->cmd_buf = buf;
			}
		}
	}
	return (w);
}

/**
 * simp_shll_get_input - the function gets a line minus the newline
 * @info: the parameter struct
 * Return: return bytes read
 */
ssize_t simp_shll_get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t w = 0;
	char **buf_p = &(info->arg), *p;

	_simp_shll_putchar(BUF_FLUSH);
	w = input_buf(info, &buf, &len);
	if (w == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		simp_shll_check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (simp_shll_is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_simp_shll_strlen(p));
	}

	*buf_p = buf;
	return (w);
}

/**
 * read_buf - this function here reads a buffer
 * @info: the parameter struct
 * @buf: the buffer
 * @i: return size
 * Return: return w
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t w = 0;

	if (*i)
		return (0);
	w = read(info->readfd, buf, READ_BUF_SIZE);
	if (w >= 0)
		*i = w;
	return (w);
}

/**
 * _simp_shll_getline - function gets the next line of input from STDIN
 * @info: the parameter struct
 * @ptr: the address of pointer to buffer, preallocated or NULL
 * @length: the size of preallocated ptr buffer if not NULL
 * Return: return s
 */
int _simp_shll_getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t w = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	w = read_buf(info, buf, &len);
	if (w == -1 || (w == 0 && len == 0))
		return (-1);

	c = _simp_shll_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _simp_shll_realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_simp_shll_strncat(new_p, buf + i, k - i);
	else
		_simp_shll_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * simp_shll_sigintHandler - the function here blocks ctrl-C
 * @sig_num: the signal number
 * Return: should be void
 */
void simp_shll_sigintHandler(__attribute__((unused))int sig_num)
{
	_simp_shll_puts("\n");
	_simp_shll_puts("$ ");
	_simp_shll_putchar(BUF_FLUSH);
}