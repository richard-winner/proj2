#include "shell.h"

/**
 * **simp_shll_strtow2 - Strings are splitted into words
 * @d: delimeter
 * @str: string input
 * Return: points to an array of str
 */

char **simp_shll_strtow2(char *str, char d)
{
	int i, q, h, v, num_wrd = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_wrd++;
	if (num_wrd == 0)
		return (NULL);
	s = malloc((1 + num_wrd) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, q = 0; q < num_wrd; q++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		h = 0;
		while (str[i + h] != d && str[i + h] && str[i + h] != d)
			h++;
		s[q] = malloc((h + 1) * sizeof(char));
		if (!s[q])
		{
			for (h = 0; h < q; h++)
				free(s[h]);
			free(s);
			return (NULL);
		}
		for (v = 0; v < h; v++)
			s[q][v] = str[i++];
		s[q][v] = 0;
	}
	s[q] = NULL;
	return (s);
}

/**
 * **simp_shll_strtow - Strings are splitted into words. Repeated delimiters are ignored
 * @d: string delimeter
 * @str: string input
 * Return: points to an array of str
 */

char **simp_shll_strtow(char *str, char *d)
{
	int i, q, h, v, num_wrd = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!simp_shll_is_delim(str[i], d) && (simp_shll_is_delim(str[i + 1], d) || !str[i + 1]))
			num_wrd++;

	if (num_wrd == 0)
		return (NULL);
	s = malloc((1 + num_wrd) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, q = 0; q < num_wrd; q++)
	{
		while (simp_shll_is_delim(str[i], d))
			i++;
		h = 0;
		while (!simp_shll_is_delim(str[i + h], d) && str[i + h])
			h++;
		s[q] = malloc((h + 1) * sizeof(char));
		if (!s[q])
		{
			for (h = 0; h < q; h++)
				free(s[h]);
			free(s);
			return (NULL);
		}
		for (v = 0; v < h; v++)
			s[q][v] = str[i++];
		s[q][v] = 0;
	}
	s[q] = NULL;
	return (s);
}
