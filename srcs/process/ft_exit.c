#include "minishell.h"
#include "environment.h"

void	ft_exit(t_process *init)
{
	if (init->input != NULL)
		free(init->input);
	ft_free_double_arr(init->processes);
	ft_lstclear(&init->env, free_envar);
	//rl_clear_history(); implicit declaration of function
	exit (0);
}
