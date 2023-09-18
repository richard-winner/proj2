#include "shell.h"

/**
 * simp_shll_interactive - the function returns true if shell is simp_shll_interactive mode
 * @info: the struct address
 * Return: 1 if simp_shll_interactive mode, else 0
 */
int simp_shll_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * simp_shll_is_delim - the function checks if character is delimeter
 * @c: this is the char to check
 * @delim: this is the delimeter string
 * Return: return 1 if true, else 0
 */
int simp_shll_is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _simp_shll_isalpha - function here checks for alphabetic character
 * @c: character to input
 * Return: return 1 if c is alphabetic, else 0
 */

int _simp_shll_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _simp_shll_atoi - function here converts a string to an integer
 * @s: string to be converted
 * Return: return 0 if no numbers in string, else converted number
 */

int _simp_shll_atoi(char *s)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}