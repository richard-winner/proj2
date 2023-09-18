#include "shell.h"

/**
 * simp_shll_get_history_file - this function gets the history file
 * @info: parameter struct
 * Return: the allocated string containg history file
 */

char *simp_shll_get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _simp_shll_getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_simp_shll_strlen(dir) + _simp_shll_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_simp_shll_strcpy(buf, dir);
	_simp_shll_strcat(buf, "/");
	_simp_shll_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * simp_shll_write_history - tjis function creates a file, or
 * appends to an existing file
 * @info: this is the parameter struct
 * Return: 1 on success, else -1
 */
int simp_shll_write_history(info_t *info)
{
	ssize_t fd;
	char *filename = simp_shll_get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_simp_shll_putsfd(node->str, fd);
		_simp_shll_putfd('\n', fd);
	}
	_simp_shll_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * simp_shll_read_history - this function reads history from file
 * @info: this is the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int simp_shll_read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = simp_shll_get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			simp_shll_build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		simp_shll_build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		simp_shll_delete_node_at_index(&(info->history), 0);
	simp_shll_renumber_history(info);
	return (info->histcount);
}

/**
 * simp_shll_build_history_list - this function adds entry to a history linked list
 * @info: this is the structure containing potential arguments
 * Used to maintain
 * @buf: the buffer
 * @linecount: this is the history linecount, histcount
 * Return: Always return 0
 */
int simp_shll_build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	simp_shll_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * simp_shll_renumber_history - function here renumbers the history
 * linked list after changes
 * @info: this is the structure containing potential arguments
 * Used to maintain
 * Return: this is the new histcount
 */
int simp_shll_renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}