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
		printf("unset: not enough arguments\n");
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if(!ft_strncmp(argv[0], "export", 7))
			export_add(&env, argv[i]);
		else if(!ft_strncmp(argv[0], "unset", 6))
			ret = unset(&env, argv[i]);
		i++;
	}
	return (ret);
}
