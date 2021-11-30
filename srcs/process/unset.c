/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:24:43 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 15:24:43 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

// replace this with validation checks
static int error = false;

void	unset(t_list **env, char *env_str)
{
	t_envar	*parse_env;
	t_list	*found;
	t_list	*prev;

	prev = NULL;
	parse_env = parse_env_var(env_str);
	if (error)
		;
	else
	{
		found = found_env(env, &prev, parse_env->name, INT_MAX);
		if (found)
		{
			prev->next = found->next;
			ft_lstdelone(found, free_envar);
		}
	}
}
