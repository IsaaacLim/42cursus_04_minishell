#include "environment.h"

/*
** Copy of JR's main.c
** Edited to be used with minishell
**	- removed argc from func arg
**	- filled t_list *env from main function, then passed over as an arg
**	- str compare argv to execute correct function
**	- ft_lstclear upon "exit"
*/
int	ft_environment(char *argv[], t_list *env)
{
	int	i;
	int	ret;

	if (!argv[1])
	{
		//only for unset because export without any arg won't reach here
		printf("unset: not enough arguments\n");
		return (1);
	}
	ret = 0;
	i = 1;
	while (argv[i])
	{
		if(!ft_strncmp(argv[0], "export", 7))
		{
			if (export_add(&env, argv[i]) != 0)
				ret = 1;
		}
		else if(!ft_strncmp(argv[0], "unset", 6))
			if (unset(&env, argv[i]) != 0)
				ret = 1;
		i++;
	}
	return (ret);
}
