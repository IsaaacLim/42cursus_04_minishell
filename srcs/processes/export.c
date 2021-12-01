/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:17:41 by jkhong            #+#    #+#             */
/*   Updated: 2021/12/01 21:03:49 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

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
