/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:17:18 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 15:17:18 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void	env_command(t_list *env)
{
	t_envar	*envar;

	while (env)
	{
		envar = (t_envar *)env->content;
		if (ft_strncmp(envar->name, "?", 2) == 0)
		{
			env = env->next;
			continue ;
		}
		if (envar->set)
			printf("%s=%s\n", envar->name, envar->word);
		env = env->next;
	}
}

int	ft_display_env(t_list *env, char **args)
{
	if (args[1])
	{
		printf("only env with no options or arguments\n");
		return (127);
	}
	else
		env_command(env);
	return (0);
}
