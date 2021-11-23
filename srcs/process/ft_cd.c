#include "minishell.h"

/*
** need "cd" or "cd ~"?
*/
int	ft_cd(char **argv)
{
	int	argc;
	argc = 0;
	while (argv[argc])
		argc++;
	// if (argc == 1)
	// 	chdir($HOME);
	if (argc == 2)
	{
		if (chdir(argv[1]) != 0)
			printf("cd: %s: No such file or directory\n", argv[1]);
	}
	else
		printf("cd: too many argumnets\n");
}
