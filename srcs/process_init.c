#include "minishell.h"
#include "environment.h"

/*
** Array of available processes
*/
char	**arr_process(void)
{
	char	**process;

	process = (char **)malloc(sizeof(char *) * 5);
	if (!process)
		ft_perror("arr_process()");
	process[0] = ft_strdup("cd");
	process[1] = ft_strdup("export");
	process[2] = ft_strdup("unset");
	process[3] = ft_strdup("exit");
	process[4] = NULL;
	return (process);
}

/*
** If ft_is_process is true, execute the corresponding process
*/
void	ft_process(t_commands *cmds, t_process init)
{
	char	**last_argv;
	char	*arg;

	last_argv = cmds->commands[cmds->len - 1].args;
	arg = last_argv[0];
	if (!ft_strncmp(arg, "cd", 3))
		ft_cd(last_argv);
	else if((!ft_strncmp(arg, "export", 7)) || (!ft_strncmp(arg, "unset", 6)))
				ft_environment(last_argv, init.env);
	else if (!ft_strncmp(arg, "exit", 5))
		ft_eval_exit(init, cmds);
}

/*
** Check whether LAST input command is a process (not built-ins)
**	*export function needs an argument
*/
bool	ft_is_process(t_commands cmds)
{
	int		i;
	char 	**last_argv;
	char	**process;
	bool	is_process;
	
	is_process = false;
	last_argv = cmds.commands[cmds.len - 1].args;
	process = arr_process();
	i = -1;
	while (process[++i])
	{
		if (!ft_strncmp(last_argv[0], "export", 7) && !last_argv[1])
			break;
		else if (!ft_strncmp(last_argv[0], process[i], 7))
			is_process = true;
	}
	ft_free_double_arr(process);
	return (is_process);
}
