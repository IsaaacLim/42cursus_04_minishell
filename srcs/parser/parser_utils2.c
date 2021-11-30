/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:07:21 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 15:07:21 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
/*
	Initialiser for t_cmd variable to 0 or NULL
*/
void	initialise_singlecmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->input = 0;
	cmd->output = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
}

t_commands	*initialise_t_commands(char **str_arr)
{
	int			cmd_len;
	t_commands	*cmds;

	cmd_len = num_pipes(str_arr) + 1;
	cmds = malloc(sizeof(t_commands));
	if (!cmds)
		return (NULL);
	cmds->commands = malloc(sizeof(t_cmd) * (cmd_len + 1));
	cmds->len = cmd_len;
	return (cmds);
}

void	free_commands(t_commands *commands)
{
	t_cmd	*cmds;
	int		i;

	if (!commands)
		return ;
	i = 0;
	cmds = commands->commands;
	while (i < commands->len)
	{
		if (cmds[i].args)
			ft_free_double_arr(cmds[i].args);
		if (cmds[i].infile)
			free(cmds[i].infile);
		if (cmds[i].outfile)
			free(cmds[i].outfile);
		i++;
	}
	free(cmds);
	free(commands);
}
