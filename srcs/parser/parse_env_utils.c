/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:57:00 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 14:57:00 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "parser.h"

/*
	Extension of found_env function
	- temporarily places null terminator char '\0' towards end of string
	- executes found_env and returns NULL if environment variable not found
*/
static t_envar	*found_null_term_env(t_list **env, char *ptr, int env_len)
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

/*
	Purpose
	- Parses str and searches t_list using found_null_term_env function above
	- updates t_envar variable if found
	- envar stores NULL if not found
	- returns environment variable name length inputted as str
*/
int	get_envlen_and_find(char *str, t_envar **envar, t_list **env, char quote)
{
	int		len;
	char	*ptr;

	ptr = str + 1;
	len = 0;
	while (ptr[len] && ptr[len] != quote && !ft_strchr(" $", ptr[len]))
		len++;
	*envar = found_null_term_env(env, ptr, len);
	return (len);
}
