#include "minishell.h"
#include "environment.h"

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

	signal(SIGQUIT, SIG_IGN);
	init.env = initialise_env(envp);
	while (1)
	{
		signal(SIGINT, ft_sig_handler);
		init.input = readline("minishell> ");
		if (init.input == NULL)
		{
			printf("exit\n");
			ft_exit(&init);
		}
		if (ft_strlen(init.input) == 0)
			continue ;
		add_history(init.input);
		read_str(init.input, &commands, &init.env);
        if (!commands)
		{
			ft_exit_status(2);
            continue ;
		}
		if (ft_is_process(*commands))
			ft_process(commands, init);
		else if (ft_strlen(init.input) > 0)
			ft_execute(*commands, init.env);
		free_commands(commands);
		init.input = NULL;
		free(init.input);
	}
	// system("leaks minishell");
}
