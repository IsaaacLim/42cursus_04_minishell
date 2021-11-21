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
		}
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(ret, NULL, 0);
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

	while (1)
	{
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
			// ft_execute(commands);
			ft_execute2(commands);
			free_commands(commands);
			free(input_arr);
		}
	}
	// system("leaks minishell");
}
