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
int	ft_environment(char *argv[], t_list *env)
{
	char	**envp;
	int		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
	{
		if (!ft_strncmp(argv[0], "env", 4))
			env_command(env);
		else if (!ft_strncmp(argv[0], "export", 7))
			export_command(env);
	}
	else if (argc == 2)
	{
		if(!ft_strncmp(argv[0], "export", 7))
			export_add(&env, argv[1]);
		else if(!ft_strncmp(argv[0], "unset", 6))
			unset(&env, argv[1]);
	}
	return (0);
}
