/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:50:11 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 13:50:11 by jkhong           ###   ########.fr       */
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
bool	valid_quotes(char *str, char *track, char to_rep, char rep_to)
{
	char	*ptr;
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
void	replace_char_in_quotes(char **str_arr, char *str,
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

/*
	Extension of found_env function
	- temporarily places null terminator char '\0' towards end of string
	- executes found_env and returns NULL if environment variable not found
*/
t_envar	*found_null_term_env(t_list **env, char *ptr, int env_len)
{
	t_list	*found;
	t_envar	*envar;
	char	c;

	c = ptr[env_len];
	ptr[env_len] = '\0';
	found = found_env(env, NULL, ptr, INT_MAX);
	ptr[env_len] = c;
	if (found)
		return ((t_envar *)(found->content));
	return (NULL);
}

int	return_env_len(char *str, t_list **env)
{
	int		tot_len;
	int		env_len;
	char	*ptr;
	t_envar	*envar;
	bool	to_update;
	char	quote;

	quote = 0;
	tot_len = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '$' && quote != '\'' && *(str + 1))
		{
			// need this to return whether to malloc a new string or not
			ptr = str + 1;
			env_len = 0;
			// check to make sure that side by side $ works as well...
			while (ptr[env_len] && ptr[env_len] != ' ' && ptr[env_len] != '$' && ptr[env_len] != quote && ptr[env_len])
				env_len++;
			envar = found_null_term_env(env, ptr, env_len);
			if (envar)
				tot_len += envar->word_len;
			str += (env_len - 1);
		}
		else
			tot_len++;
		str++;
	}
	return (tot_len);
}

char	*update_with_env(char *str, t_list **env, int tot_len)
{
	char	*tmp;
	int		i;
	int		env_len;
	char	*ptr;
	t_envar	*envar;
	char	quote;

	quote = 0;
	tmp = malloc(sizeof(char) * (tot_len + 1));
	i = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '$' && quote != '\'' && *(str + 1))
		{
			ptr = str + 1;
			env_len = 0;
			while (ptr[env_len] && ptr[env_len] != ' ' && ptr[env_len] != '$' && ptr[env_len] != quote && ptr[env_len])
				env_len++;
			envar = found_null_term_env(env, ptr, env_len);
			if (envar)
			{
				ft_memcpy(&tmp[i], envar->word, envar->word_len);
				i += envar->word_len;
			}
			str += env_len;
		}
		else
			tmp[i++] = *str;
		str++;
	}
	tmp[tot_len] = '\0';
	return (tmp);
}

char	*check_update_env(char *str, t_list **env)
{
	int	len;

	len = return_env_len(str, env);
	return (update_with_env(str, env, len));
}
