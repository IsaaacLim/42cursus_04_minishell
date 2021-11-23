#include "environment.h"

/*
** Copy of JR's main.c
** Edited to be used with minishell
**	- removed argc
**	- str compare argv
*/
int	ft_environment(char *argv[])
{
	t_list *env;
	char	**envp;
	int		argc;

	argc = 0;
	while (argv[argc])
		argc++;
	env = initialise_env(envp);
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

	// to free -> include towards end of main
	ft_lstclear(&env, free_envar);
	return (0);
}
