#include "minishell.h"
#include "environment.h"

void	ft_exit(t_process *init)
{
	if (init->input != NULL)
		free(init->input);
	ft_lstclear(&init->env, free_envar);
	//rl_clear_history(); implicit declaration of function
	exit (0);
}

void	ft_eval_exit(t_process init, char **argv)
{
	int	argc;

	argc = 1;
	// printf("%s\n", argv[argc]);
	while (argv[argc])
		argc++;
	if (argc > 2)
	{
		g_exit_status = 1;
		printf("exit: too many arguments\n");
		return ;
	}
	else if(argc == 2)
		g_exit_status = ft_atoi(argv[1]);
	else
		g_exit_status = 0;
	ft_free_double_arr(argv);
	ft_exit(&init);
}
