#include "minishell.h"
#include "environment.h"
#include "get_next_line.h"

/*
** Readline
**	If argc > 0, evaluate input as process/executables
*/
int	main(int argc, char *argv[], char *envp[])
{
	t_commands	*commands;
	t_process	init;

	init.env = initialise_env(envp);
	init.processes = arr_process();
	while (1)
	{
		init.input = readline("Enter text: ");
		if (ft_strlen(init.input) == 0)
			continue ;
		add_history(init.input);
		if (ft_is_process(init.input, init.processes))
			ft_process(init);
		else if (ft_strlen(init.input) > 0)
		{
			read_str(init.input, &commands);
			ft_execute(*commands, init.env);
			free_commands(commands);
		}
		free(init.input);
	}
	// system("leaks minishell");
}
