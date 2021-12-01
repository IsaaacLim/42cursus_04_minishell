/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:16:40 by jkhong            #+#    #+#             */
/*   Updated: 2021/12/01 17:45:35 by jinlim           ###   ########.fr       */
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

/*
	Constructs list of single commands t_cmd
	(i) split str read from readline
	(ii) validates redirection and pipe
	(iii) also validates quotation indirectly via str_arr return val
*/
t_commands	*parse_commands(char *str, t_list **env)
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

int	read_str(char *str, t_commands **commands, t_list **env)
{
	*commands = parse_commands(str, env);
	if (!*commands)
	{
		perror("Syntax error near unexpected token");
		ft_exit_status(2);
		return (2);
	}
	return (0);
}
