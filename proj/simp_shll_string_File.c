#include "shell.h"

/**
 * _simp_shll_strlen - gives the length of a string
 * @s: the string length to be checkec
 * Return: integer length of string
 */

int _simp_shll_strlen(char *s)
{
	int z = 0;

	if (!s)
		return (0);

	while (*s++)
		z++;
	return (z);
}

/**
 * simp_shll_starts_with - performs a check to see if needle starts with an haystack
 * @needle: the substring to find
 * @haystack: the string to search
 * Return: returns the address of the next char of haystack
 */

char *simp_shll_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _simp_shll_strcat - adds two strings together
 * @src: the source buff
 * @dest: the destination buff
 * Return: pointer to destination buff
 */

char *_simp_shll_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _simp_shll_strcmp - exicogarphic comparison of two strangs.
 * @s1: strang 1
 * @s2: strang 2
 * Return: negative if s1 is less than s2,
 * positive if s1 is greater than s2, and zero if s1 is equal to s2
 */

int _simp_shll_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}