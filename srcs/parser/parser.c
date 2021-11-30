/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:16:40 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 01:01:08 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*
	Considerations for redirection
	Edge cases for handling redirection
		- redirection must be an arrow followed by a filename
	Sequence doesn't matter
		- > hi cat < README.md
	Prompts syntax error if missing filename
		- > [missing filename]
		- [missing filename] <
*/

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

/*
	Purpose:
	- Scans str_arr and returns arg_len
	- Deduct 2 * redir because each redirection would have an arrow and filename
*/
int	calc_arg_len(char **str_arr, t_cmd *cmd)
{
	int	i;
	int	redir;

	i = 0;
	redir = 0;
	initialise_singlecmd(cmd);
	while (str_arr[i] && ft_strncmp(str_arr[i], "|", INT_MAX) != 0)
	{
		if (is_redirection(str_arr[i], cmd, str_arr[i + 1]))
			redir++;
		i++;
	}
	return (i - (2 * redir));
}

/*
	Purpose:
	Returns a t_cmd variable which contains:
	(i) arguments in type (char **)
	(ii) redirection for input and output
	(iii) if redirection is necessary, filename of infile and outfile
	Steps:
	1. Initialise t_cmd
	2. Updates redirection and calculates argument length (ignore pipe |)
		checks str_arr is not NULL
*/
t_cmd	parse_singlecmd(char **str_arr, t_list **env)
{
	int		i;
	int		j;
	int		arg_len;
	int		redir;
	t_cmd	cmd;

	j = 0;
	arg_len = calc_arg_len(str_arr, &cmd);
	cmd.args = malloc(sizeof(char *) * (arg_len + 1));
	i = 0;
	while (str_arr[i] && ft_strncmp(str_arr[i], "|", INT_MAX) != 0)
	{
		if (is_redirection(str_arr[i], NULL, NULL))
			i += 2;
		else
		{
			(cmd.args)[j++] = check_update_env(str_arr[i], env);
			i++;
		}
	}
	(cmd.args)[arg_len] = NULL;
	return (cmd);
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

t_commands *parse_commands(char *str, t_list **env)
{
	char		**str_arr;
	t_commands	*cmds;
	int			i;
	int			j;

	i = 0;
	j = 0;
	str_arr = ft_split_enhanced(str, ' ');
	if (str_arr && valid_redirection(str_arr) && valid_pipe(str_arr))
	{
		cmds = initialise_t_commands(str_arr);
		while (str_arr[i])
		{
			if (i == 0 || ft_strncmp(str_arr[i - 1], "|", INT_MAX) == 0)
				(cmds->commands)[j++]
					= parse_singlecmd(&str_arr[i], env);
			i++;
		}
	}
	else
		cmds = NULL;
	ft_free_double_arr(str_arr);
	return (cmds);
}

void	read_str(char *str, t_commands **commands, t_list **env)
{
	*commands = parse_commands(str, env);
	if (!*commands)
	{
		printf("Syntax error near unexpected token\n");
		return ;
	}
}
