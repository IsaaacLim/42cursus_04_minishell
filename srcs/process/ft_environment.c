#include "environment.h"

/*
** Copy of JR's main.c
** Edited to be used with minishell
**	- removed argc from func arg
**	- filled t_list *env from main function, then passed over as an arg
**	- str compare argv to execute correct function
**	- ft_lstclear upon "exit"
**
** GOT ISSUE WHEN EXECUTING THIS FUNCTION > ONCE
*/
void	ft_environment(char *argv[], t_list *env)
{
	char	**envp;
	int		argc;
	int		i;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc < 2)
	{
		printf("ft_environment: too little arg. Not supposed to reach here\n");
		return ;
	}
	i = 1;
	while (argc > 1 && argv[i])
	{
		if(!ft_strncmp(argv[0], "export", 7))
			export_add(&env, argv[i]);
		else if(!ft_strncmp(argv[0], "unset", 6))
			unset(&env, argv[i]);
		i++;
	}
}
