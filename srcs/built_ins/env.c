/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:59:27 by jinlim            #+#    #+#             */
/*   Updated: 2021/12/01 19:59:28 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	j;

	if (argc != 1)
	{
		printf("env: execute without options or arguments\n");
		return (127);
	}
	i = -1;
	while (envp[++i])
	{
		if (envp[i][0] == '?' && envp[i][1] == '=')
			continue ;
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		if (envp[i][j + 1])
			printf("%s\n", envp[i]);
	}
	return (0);
}
