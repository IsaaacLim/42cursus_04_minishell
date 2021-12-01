/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:17:41 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 18:17:41 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
	Purpose:
	Sorts environment variable (t_envar) by NAME in alphabetical order
*/
static void	sort_env(t_envar ***env, int len)
{
	int		i;
	int		j;
	t_envar	**ptr;
	t_envar	*tmp;

	ptr = *env;
	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(ptr[i]->name, ptr[j]->name, INT_MAX) > 0)
			{
				tmp = ptr[i];
				ptr[i] = ptr[j];
				ptr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

/*
	Adds additional variable into env struct
*/
int	export_add(t_list **env, char *env_str)
{
	t_envar		*parse_env;
	t_list		*found;

	parse_env = parse_env_var(env_str);
	if (!valid_identifier(parse_env->name))
	{
		invalid_identifier_msg("export", parse_env->name);
		free_envar((void *)parse_env);
		return (1);
	}
	found = found_env(env, NULL, parse_env->name, INT_MAX);
	if (!found)
		ft_lstadd_back(env, ft_lstnew((void *)parse_env));
	else
	{
		free_envar(found->content);
		found->content = parse_env;
	}
	return (0);
}
