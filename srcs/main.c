#include "minishell.h"
#include "environment.h"

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

	process = (char **)malloc(sizeof(char *) * 6);
	if (!process)
		ft_perror("arr_process()");
	process[0] = ft_strdup("cd");
	process[1] = ft_strdup("env");
	process[2] = ft_strdup("export");
	process[3] = ft_strdup("unset");
	process[4] = ft_strdup("exit");
	process[5] = NULL;
	return (process);
}

void	ft_exit(t_process *init)
{
	free(init->input);
	ft_free_double_arr(init->processes);
	ft_lstclear(&init->env, free_envar);
	// rl_clear_history(); //implicit declaration of function
	exit (0);
}

void	ft_chdir(char *input_arr)
{
	char **split;

	split = ft_split(input_arr, ' ');
	chdir(split[1]);
	ft_free_double_arr(split);
}

void	ft_process(t_process init)
{
	char	**split;
	char	*arg;

	split = ft_split(init.input, ' ');
	arg = split[0];
	if (!ft_strncmp(arg, "cd", 3))
		ft_chdir(init.input);
	else if((!ft_strncmp(arg, "env", 4)) ||
		(!ft_strncmp(arg, "export", 7)) || (!ft_strncmp(arg, "unset", 6)))
		ft_environment(split, init.env);
	else if (!ft_strncmp(init.input, "exit", 5))
	{
		ft_free_double_arr(split);
		ft_exit(&init);
	}
	ft_free_double_arr(split);
}

bool	ft_is_process(char *input, char **processes)
{
	int		i;
	char 	**split;
	bool	is_process;

	is_process = false;
	split = ft_split(input, ' ');
	i = -1;
	while (processes[++i])
	{
		if (!ft_strncmp(split[0], processes[i], 20)) //just change to strnstr
			is_process = true;
	}
	ft_free_double_arr(split);
	return (is_process);
}

/*
** Contains previous ft_readline codes
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
		if (ft_is_process(init.input, init.processes))
			ft_process(init);
		else if (ft_strlen(init.input) > 0)
		{
			add_history(init.input);
			read_str(init.input, &commands);
			// ft_execute(commands);
			ft_execute2(commands);
			// ft_execute3(commands);
			free_commands(commands);
			free(init.input);
		}
	}
	// system("leaks minishell");
}
