/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:51:42 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 17:51:42 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "libft.h"

/*
	Definition of valid identifier
	https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Definitions
	name
	A word consisting solely of letters, numbers, and underscores,
	and beginning with a letter or underscore. Names are used as shell variable
	and function names. Also referred to as an identifier.
*/
bool	valid_identifier(char *str)
{
	if (!(ft_isalpha(*str) || *str == '_'))
		return (false);
	str++;
	while (*str)
	{
		if (!(ft_isalpha(*str) || ft_isdigit(*str) || *str == '_'))
			return (false);
		str++;
	}
	return (true);
}

void	invalid_identifier_msg(char *cmd, char *name)
{
	perror(cmd);
	perror(": \'");
	perror(name);
	perror("': not a valid identifier\n");
}
