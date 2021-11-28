#include "minishell.h"
#include "environment.h"

t_process	g_init;

/*
** signal(SIGQUIT, SIG_IGN); ignores display but can't update EXIT
*/
void	ft_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		export_add(&g_init.env, "EXIT=130");
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		export_add(&g_init.env, "EXIT=131");
		printf("%c%c", 8, 8);
	}
	return ;
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
	t_commands	*commands;

	signal(SIGQUIT, ft_sig_handler);
	g_init.env = initialise_env(envp);
	g_init.processes = arr_process();
	while (1)
	{
		signal(SIGINT, ft_sig_handler);
		g_init.input = readline("minishell> ");
		if (g_init.input == NULL)
		{
			printf("exit\n");
			ft_exit(&g_init);
		}
		if (ft_strlen(g_init.input) == 0)
			continue ;
		add_history(g_init.input);
		if (ft_is_process(g_init.input, g_init.processes))
			ft_process(g_init);
		else if (ft_strlen(g_init.input) > 0)
		{
			read_str(g_init.input, &commands);
			ft_execute(*commands, g_init.env);
			free_commands(commands);
		}
		g_init.input = NULL;
		free(g_init.input);
	}
	// system("leaks minishell");
}
