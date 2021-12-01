/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_enhanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:54:59 by jkhong            #+#    #+#             */
/*   Updated: 2021/12/01 20:59:26 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "parser.h"

/*
	Validates string to determine if there are unclosed quotes
	- includes single ('') and double quotes ("")
	- quotes nested within quotes are not validated
		- e.g. "'" is valid
*/
static bool	valid_quotes(char *str, char *track, char to_rep, char rep_to)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (quote && *str == to_rep)
		{
			*track = 1;
			*str = rep_to;
		}
		else if (*str == quote)
			quote = 0;
		else if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		str++;
		track++;
	}
	if (quote)
		return (false);
	return (true);
}

/*
	Purpose:
	- replaces characters which are enclosed in quotes
	- does not include nested quotes
	Use case:
	- to temporarily replace spaces in quotes for subsequent ease of use of ft_split
*/
static void	replace_char_in_quotes(char **str_arr, char *str,
			char *track, char rep_to)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (track[i] == 1)
				(*str_arr)[j] = rep_to;
			j++;
			if ((*str_arr)[j] == '\0')
			{
				str_arr++;
				j = 0;
			}
		}
		i++;
	}
}

/*
	Purpose:
	Enhanced version of ft_split to consider:
	i. validity of quotes
	ii. spaces within quotes (handled by temporarily replacing with non ' ' value)
	Returns
	- char ** if valid
	- NULL if quotation is invalid	
*/
char	**ft_split_enhanced(char *str, char c)
{
	char	**str_arr;
	char	*track;

	track = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	str_arr = NULL;
	if (valid_quotes(str, track, c, -1))
	{
		str_arr = ft_split(str, c);
		replace_char_in_quotes(str_arr, str, track, c);
	}
	free(track);
	return (str_arr);
}
