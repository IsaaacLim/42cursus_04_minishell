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

/*
	Purpose:
	1. Verification of whether str relates to a redirection
	2. Updates t_cmd variable for redirection found.
	   t_cmd variable is initialised to zero previously if not updated
	3. Four types of redirections:
	- << & char *
	- < & char *
	- > & char *
	- >> & char * 
	4. Returns 0 (not found) or integer value (found)
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

/*
	Purpose:
	Validates if redirection is followed by a filename
	Returns:
	false if followed by (i) nothing or (ii) pipe
	true if followed by filename
*/
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

/*
	Validates if pipe is valid:
	Returns false if:
	(i) first str arg is a pipe (index 0)
	(ii) next string is a pipe
	(iii) pipe is the last str in the array
*/
bool	valid_pipe(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
	{
		if (i == 0 && ft_strncmp(str_arr[i], "|", INT_MAX) == 0)
			return (false);
		if (ft_strncmp(str_arr[i], "|", INT_MAX) == 0)
		{
			if (str_arr[i + 1] == NULL
				|| ft_strncmp(str_arr[i - 1], "|", INT_MAX) == 0
				|| ft_strncmp(str_arr[i + 1], "|", INT_MAX) == 0)
				return (false);
		}
		i++;
	}
	return (true);
}
