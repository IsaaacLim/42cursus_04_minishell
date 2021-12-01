/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:14:20 by jinlim            #+#    #+#             */
/*   Updated: 2021/12/01 21:14:21 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_eval_exit(t_process init, t_commands *cmds)
{
	char	**last_argv;
	int		argc;

	last_argv = cmds->commands[cmds->len - 1].args;
	argc = 1;
	while (last_argv[argc])
		argc++;
	if (argc > 2)
	{
		ft_exit_status(1);
		printf("exit: too many arguments\n");
		return ;
	}
	else if(argc == 2)
		ft_exit_status(ft_atoi(last_argv[1]));
	else
		ft_exit_status(0);
	free_commands(cmds);
	ft_exit(&init);
}
