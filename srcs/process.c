/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:07:54 by jinlim            #+#    #+#             */
/*   Updated: 2021/12/01 19:09:19 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

/*
** If ft_is_process is true, execute the corresponding process
*/
void	ft_process(t_commands *cmds, t_process init)
{
	char	**last_argv;
	char	*arg;

	last_argv = cmds->commands[cmds->len - 1].args;
	arg = last_argv[0];
	if (!ft_strncmp(arg, "cd", 3))
		ft_exit_status(ft_cd(last_argv, init.env));
	else if ((!ft_strncmp(arg, "export", 7)) || (!ft_strncmp(arg, "unset", 6)))
		ft_exit_status(ft_environment(last_argv, init.env));
	else if (!ft_strncmp(arg, "exit", 5))
		ft_eval_exit(init, cmds);
}

/*
** Check whether LAST input command is a process (not built-ins)
**	*export function needs an argument
*/
bool	ft_is_process(t_commands cmds)
{
	int			i;
	char		**last_argv;
	static char	*process[4] = {
		"cd",
		"export",
		"unset",
		"exit"
	};

	last_argv = cmds.commands[cmds.len - 1].args;
	i = -1;
	while (++i < 4)
	{
		if (!ft_strncmp(last_argv[0], "export", 7) && !last_argv[1])
			break ;
		else if (!ft_strncmp(last_argv[0], process[i], 7))
			return (true);
	}
	return (false);
}
