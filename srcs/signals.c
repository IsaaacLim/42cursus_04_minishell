/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:02:48 by jinlim            #+#    #+#             */
/*   Updated: 2021/12/02 17:46:09 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

/*
** Ignore SIGINT
**	Only declared in int main()
*/
void	ft_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_exit_status(130);
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

/*
** Ignore EOF input (ctrl-D)
** may show value of EOF character with (int)term1.c_cc[VEOF]
**	Only declared in ft_heredoc()
*/
void	ft_sig_ignore_eof(bool ignore)
{
	struct termios	term1;

	if (tcgetattr(STDIN_FILENO, &term1) != 0)
		perror("tcgetattr error");
	else
	{
		if (ignore)
			term1.c_cc[VEOF] = 0;
		else
			term1.c_cc[VEOF] = 04;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
			perror("tcsetattr() error");
		if (tcgetattr(STDIN_FILENO, &term1) != 0)
			perror("tcgetattr() error");
	}
}
