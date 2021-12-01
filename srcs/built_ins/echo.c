/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:23:06 by jkhong            #+#    #+#             */
/*   Updated: 2021/12/01 20:30:51 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>

/*
	Working inputs
	1. echo 		- no arguments
	2. echo <arg1> 	- 1 argument
	3. echo <arg1 ... <arg3> - multiple arguments
	4. echo -n 		- no arg + no new line
	5. echo -n <arg1> & multiple arguments
*/
int	main(int argc, char *argv[])
{
	int		i;
	bool	nl;

	i = 1;
	nl = true;
	if (argc >= 2 && argv[1][0] == '-' && argv[1][1] == 'n' && !argv[1][2])
	{
		i = 2;
		nl = false;
	}
	while (i < argc)
	{
		if ((nl && i > 1) || (!nl && i > 2))
			printf(" ");
		printf("%s", argv[i]);
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
