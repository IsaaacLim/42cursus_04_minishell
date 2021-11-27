#include "minishell.h"
#include "environment.h"

t_process	g_init;

void	ft_signint()
{
	printf("Sigint with C parent\n");
	ft_exit (&g_init);
}

void	ft_sigquit()
{
	// printf("Sigquit with \\\n");
	return ;
}

/*
** Readline
**	If argc > 0, evaluate input as process/executables
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_commands	*commands;

	signal(SIGINT, ft_signint);
	signal(SIGQUIT, SIG_IGN);
	g_init.env = initialise_env(envp);
	g_init.processes = arr_process();
	while (1)
	{
		g_init.input = readline("Enter text: ");
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
