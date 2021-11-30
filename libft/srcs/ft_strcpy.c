/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:27:09 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 18:27:09 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(ft_strlen(str) + 1));
	while (*str)
	{
		tmp[i++] = *str;
		str++;
	}
	tmp[i] = '\0';
	return (tmp);
}