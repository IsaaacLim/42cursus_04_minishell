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

// void	ft_eval_exit(t_process init, char **argv)
// {
// 	if (!argv[1])
// 	{
// 		ft_free_double_arr(argv);
// 		ft_exit(&init);
// 	}
// 	else if (argv[2])
// 		g_exit_status = 1;
// 	else if(argv[1])

// }
