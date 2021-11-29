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
void	ft_process(t_process init)
{
	char	**argv;
	char	*arg;

	argv = ft_split(init.input, ' ');
	arg = argv[0];
	if (!ft_strncmp(arg, "cd", 3))
		ft_cd(argv);
	else if((!ft_strncmp(arg, "export", 7)) || (!ft_strncmp(arg, "unset", 6)))
				ft_environment(argv, init.env);
	else if (!ft_strncmp(init.input, "exit", 5))
	{
		ft_free_double_arr(argv);
		ft_exit(&init);
	}
	ft_free_double_arr(argv);
}

/*
** Check whether input command is a process (not built-ins)
** ft_sdtrncmp with 20 characters is a random number
*/
bool	ft_is_process(char *input)
{
	int		i;
	char 	**argv;
	char	**process;
	bool	is_process;

	is_process = false;
	argv = ft_split(input, ' ');
	process = arr_process();
	i = -1;
	while (process[++i])
	{
		if (!ft_strncmp(argv[0], "export", 7) && !argv[1])
			break;
		else if (!ft_strncmp(argv[0], process[i], 7))
			is_process = true;
	}
	ft_free_double_arr(argv);
	ft_free_double_arr(process);
	return (is_process);
}
