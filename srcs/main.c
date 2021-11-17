#include "minishell.h"

/*
** Parsing structure follows print_commands()
*/
void	ft_execute(t_commands *cmds)
{
	int				i;
	char			**args;
	t_subprocess	p;

	// print_commands(cmds); //test
	i = 0;
	while (i < cmds->len)
	{
		args = cmds->commands[i].args;
		ft_fork(cmds->commands[i], &p);
		i++;
	}
}

/*
** Contains previous ft_readline codes
*/
int	main(int argc, char *argv[])
{
	t_commands		*commands;
	t_subprocess	p;

	char	*input_arr;
	t_input	input;

	// while (1)
	// {
		input_arr = readline("Enter text: ");
		if (!ft_strncmp(input_arr, "exit", 5))
		{
			free(input_arr);
			// rl_clear_history(); //implicit declaration of function
			return (0);
		}
		else if (ft_strlen(input_arr) > 0)
		{
			add_history(input_arr);
			read_str(input_arr, &commands);
			ft_execute(commands);
			free_commands(commands);
			free(input_arr);
		}
	// }
	// system("leaks minishell");
}
