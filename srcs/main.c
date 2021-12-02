/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:18:25 by jinlim            #+#    #+#             */
/*   Updated: 2021/12/02 16:29:16 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

static void	welcome(void)
{
	printf(""
		BOLD KBLU"           _      "KGRN" _     _   "KCYN"       _"KMAG" _ \n"
		KRED " _ __ ___"KBLU" (_)_ __ "KGRN"(_)___| |_"KCYN"_   ___| "KMAG"| |\n"
		KRED "| '_ ` "KBLU"_ \\| | '"KGRN"_ \\| / __|"KCYN" '_ \\ / _"KMAG" \\ | |\n"
		KRED"| | | "KBLU"| | | | |"KGRN" | | \\__ \\"KCYN" | | | "KMAG" __/ | |\n"
		KRED"|_| "KBLU"|_| |_|_|"KGRN"_| |_|_|___"KCYN"/_| |_|\\"KMAG"___|_|_|\n"
		RST KYEL"	  	     by: jinlim & jkhong\n\n"RST);
}

static char	*give_minishell(void)
{
	static char	*str[4] = {
		BOLD KRED"minishell> "RST,
		BOLD KGRN"minishell> "RST,
		BOLD KBLU"minishell> "RST,
		BOLD KCYN"minishell> "RST
	};
	static int	i = 0;

	i++;
	return (str[i % 4]);
}

static bool	is_empty_input(char *input, t_process init)
{
	if (input == NULL)
	{
		printf("exit\n");
		ft_exit(&init);
	}
	else if (ft_strlen(input) == 0)
		return (true);
	return (false);
}

/*
** Readline
** 	If input == NULL 
**		when input is blank and ctrl-D is entered
**	If input == 0
**		when input is blank and Enter key is entered	 
**	If argc > 0, evaluate input as process/executables
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_process	init;
	t_commands	*commands;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	welcome();
	init.env = initialise_env(envp);
	while (1)
	{
		signal(SIGINT, ft_sig_handler);
		init.input = readline(give_minishell());
		if (is_empty_input(init.input, init))
			continue ;
		add_history(init.input);
		if (read_str(init.input, &commands, &init.env) == 2)
			continue ;
		if (ft_is_process(*commands))
			ft_process(commands, init);
		else if (ft_strlen(init.input) > 0)
			ft_execute(*commands, init.env);
		free_commands(commands);
		init.input = NULL;
		free(init.input);
	}
}
