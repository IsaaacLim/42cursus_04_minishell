#include "minishell.h"

/*
** Forks for child process to run execve for each commands
*/
void	ft_execute(t_commands *cmds)
{
	int				i;
	t_subprocess	p;
	bool			first_command;
	bool			last_command;

	// print_commands(cmds); //test
	first_command = true;
	last_command = false;
	i = 0;
	while (i < cmds->len)
	{
		if (i != 0)
			first_command = false;
		if (i == cmds->len - 1)
			last_command = true;
		ft_fork(cmds->commands[i], &p, first_command, last_command);
		i++;
	}
}

/*
** Sample from purdue.edu pdf on pipes
*/
void	ft_execute2(t_commands *cmds)
{
	int tmpin=dup(0);
	int tmpout=dup(1);
	
	int	fdin;
	fdin = dup(tmpin);

	int	ret;
	int	fdout;
	for (int i = 0; i < cmds->len; i++)
	{
		if (cmds->commands[i].input == in)
		{
			fdin = open(cmds->commands[i].infile, O_RDONLY | O_CLOEXEC, 0777);
			if (fdin < 0)
				perror("fdin open");
		}
		dup2(fdin, 0);
		close(fdin);
		if (i == cmds->len - 1)
		{
			if (cmds->commands[i].output)
			{
				fdout = open(cmds->commands[i].outfile, O_WRONLY | O_TRUNC | O_CREAT | O_CLOEXEC, 0777);
				if (fdin < 0)
					perror("fdin open");
			}
			else
				fdout = dup(tmpout);
		}
		else
		{
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout,1);
		close(fdout);

		ret = fork();
		if (ret == 0)
		{
			char *envp[] = {NULL};
			execve(cmds->commands[i].args[0], cmds->commands[i].args, envp);
			printf("command not found: %s\n", cmds->commands[i].args[0]);
			exit (1);
		}
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(ret, NULL, 0);
}

/*
** Array of available processes
*/
char	**arr_process()
{
	char	**process;
	int		i;

	i = 3;
	process = (char **)malloc(sizeof(char *) * i);
	process[0] = ft_strdup("exit");
	process[1] = ft_strdup("cd");
	process[i - 1] = NULL;
	return (process);
}

void	ft_exit(char *input_arr, char **process)
{
	free(input_arr);
	ft_free_double_arr(process);
	// rl_clear_history(); //implicit declaration of function
	exit (0);
}

void	ft_process(char *input_arr, char **process)
{
	if (!ft_strncmp(input_arr, "exit", 5))
		ft_exit(input_arr, process);
	else if (!ft_strncmp(input_arr, "cd", 3))
		printf("cd\n");
}

bool	ft_is_process(char *input_arr, char **process)
{
	int	i;

	i = -1;
	while (process[++i])
	{
		if (!ft_strncmp(input_arr, process[i], 10))
			return (true);
	}
	return (false);
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
	char			**process;
	int				i;

	process = arr_process();
	while (1)
	{
		input_arr = readline("Enter text: ");
		if (ft_is_process)
			ft_process(input_arr, process);
		else if (ft_strlen(input_arr) > 0)
		{
			add_history(input_arr);
			read_str(input_arr, &commands);
			// ft_execute(commands);
			ft_execute2(commands);
			// ft_execute3(commands);
			free_commands(commands);
			free(input_arr);
		}
	}
	// system("leaks minishell");
}
