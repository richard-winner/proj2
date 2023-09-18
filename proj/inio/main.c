#include "shell.h"

/**
 * main - Point on entry
 * @av: Argument vector
 * @ac: Argument count
 * Return: On success 0, on error 1
 */


int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int bc = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (bc)
			: "r" (bc));

	if (ac == 2)
	{
		bc = open(av[1], O_RDONLY);
		if (bc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_simp_shll_eputs(av[0]);
				_simp_shll_eputs(": 0: Can't open ");
				_simp_shll_eputs(av[1]);
				_simp_shll_eputchar('\n');
				_simp_shll_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = bc;
	}
	simp_shll_populate_env_list(info);
	simp_shll_read_history(info);
	simp_shll_hsh(info, av);
	return (EXIT_SUCCESS);
}
