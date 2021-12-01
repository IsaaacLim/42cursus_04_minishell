/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:45:40 by jkhong            #+#    #+#             */
/*   Updated: 2021/12/01 17:45:40 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int	ft_environment(char *argv[], t_list *env)
{
	int	i;
	int	ret;

	if (!argv[1])
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	ret = 0;
	i = 1;
	while (argv[i])
	{
		if (!ft_strncmp(argv[0], "export", 7))
		{
			if (export_add(&env, argv[i]) != 0)
				ret = 1;
		}
		else if (!ft_strncmp(argv[0], "unset", 6))
			if (unset(&env, argv[i]) != 0)
				ret = 1;
		i++;
	}
	return (ret);
}
