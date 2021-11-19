/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:16:18 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/19 17:52:47 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	num_pipes(char **str_arr)
{
	int		pipes;

	pipes = 0;
	while (*str_arr)
	{
		if (ft_strncmp(*str_arr, "|", INT_MAX) == 0)
			pipes++;
		str_arr++;
	}
	return (pipes);
}

// TODO - free commands
// TODO - process error

/*
	This somehow works
	- cat -n < what
	- cat < what -n

*/

/*
	4 Scenarios
	- << & char *
	- < & char *
	- > & char *
	- >> & char *

	Check against str_arr + 1 incase its null terminated

	returns redirection enum,
	0 would mean a redirection is not found
*/
int	is_redirection(char *str, t_cmd *cmd, char *next)
{
	int	redir;

	redir = 0;
	if (ft_strncmp(str, "<", INT_MAX) == 0)
		redir = in;
	else if (ft_strncmp(str, "<<", INT_MAX) == 0)
		redir = in_heredoc;
	else if (ft_strncmp(str, ">", INT_MAX) == 0)
		redir = out;
	else if (ft_strncmp(str, ">>", INT_MAX) == 0)
		redir = out_append;
	if (cmd)
	{
		if (redir == in || redir == in_heredoc)
		{
			cmd->input = redir;
			cmd->infile = ft_strcpy(next);
		}
		else if (redir == out || redir == out_append)
		{
			cmd->output = redir;
			cmd->outfile = ft_strcpy(next);
		}
	}
	return (redir);
}

bool	valid_redirection(char **str_arr)
{
	while (*str_arr)
	{
		if (is_redirection(*str_arr, NULL, NULL))
		{
			if (*(str_arr + 1) == NULL
				|| ft_strncmp(*(str_arr + 1), "|", INT_MAX) == 0)
				return (false);
		}
		str_arr++;
	}
	return (true);
}

bool	valid_pipe(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
	{
		// return false if pipe is first arg
		if (i == 0 && ft_strncmp(str_arr[i], "|", INT_MAX) == 0)
			return (false);
		if (ft_strncmp(str_arr[i], "|", INT_MAX) == 0)
		{
			// checks if previous/next arg is pipe, and if next is NULL
			if (str_arr[i + 1] == NULL
				|| ft_strncmp(str_arr[i - 1], "|", INT_MAX) == 0
				|| ft_strncmp(str_arr[i + 1], "|", INT_MAX) == 0)
				return (false);
		}
		i++;
	}
	return (true);
}
