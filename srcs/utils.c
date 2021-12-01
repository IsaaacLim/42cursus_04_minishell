/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:22:05 by jinlim            #+#    #+#             */
/*   Updated: 2021/12/01 18:22:50 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Set global exit status
** Helper function for $?
*/
void	ft_exit_status(int exit_status)
{
	int		status_len;
	char	*ptr;

	if (exit_status >= 100)
		status_len = 3;
	else if (exit_status >= 10)
		status_len = 2;
	else
		status_len = 1;
	g_exstat.exit_status = exit_status;
	g_exstat.env->word_len = status_len;
	ptr = g_exstat.env->word;
	ptr[status_len] = '\0';
	while (--status_len >= 0)
	{
		ptr[status_len] = (exit_status % 10) + '0';
		exit_status /= 10;
	}
}

/*
** Used as error handling for UNEXPECTING libft functions
** exit program if occurs
*/
void	ft_libft_error(char *strerror)
{
	printf("libft error: %s\n", strerror);
	exit (42);
}

/*
** Used as error handling for UNEXPECTING library functions
** exit program if occurs
*/
void	ft_perror_exit(char *message)
{
	perror(message);
	exit (24);
}

void	ft_free_double_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		i++;
	while (--i >= 0)
	{
		ft_bzero(arr[i], ft_strlen(arr[i]));
		free(arr[i]);
	}
	free(arr);
	return ;
}
