#include "shell.h"

/**
 **_simp_shll_strncpy - the function here copies a string
 *@dest: rep destination string to be copied to
 *@src: rep source string
 *@n: the amount of characters to be copied
 *Return: return the concatenated string
 */
char *_simp_shll_strncpy(char *dest, char *src, int n)
{
	int v, z;
	char *s = dest;

	v = 0;
	while (src[v] != '\0' && v < n - 1)
	{
		dest[v] = src[v];
		v++;
	}
	if (v < n)
	{
		z = v;
		while (z < n)
		{
			dest[z] = '\0';
			z++;
		}
	}
	return (s);
}

/**
 **_simp_shll_strncat - the function here concatenates two strings
 *@dest: this is the first string
 *@src: this is the second string
 *@n: this is the amount of bytes to be maximally used
 *Return: return the concatenated string
 */
char *_simp_shll_strncat(char *dest, char *src, int n)
{
	int v, z;
	char *s = dest;

	v = 0;
	z = 0;
	while (dest[v] != '\0')
		v++;
	while (src[z] != '\0' && z < n)
	{
		dest[v] = src[z];
		v++;
		z++;
	}
	if (z < n)
		dest[v] = '\0';
	return (s);
}

/**
 **_simp_shll_strchr - function locates a character in a string
 *@s: string to be parsed
 *@c: character to look for
 *Return: should return (s) a pointer to the memory area s
 */
char *_simp_shll_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
