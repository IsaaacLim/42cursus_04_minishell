#include "minishell.h"
#include "get_next_line.h"

void	ft_redir_in(t_cmd commands, int fdin)
{
	char *line;
	int	ret;
	int fdtemp[2];

	if (commands.input == in)
	{
		fdin = open(commands.infile, O_RDONLY | O_CLOEXEC, 0777);
		if (fdin < 0)
			perror("infile failed to open");
	}
	else if (commands.input == in_heredoc)
	{
		pipe(fdtemp);
		write(1, "heredoc> ", 9);
		ret = get_next_line(0, &line);
		while (ret > 0)
		{
			if (!ft_strncmp(line, commands.infile, ft_strlen(commands.infile) + 1))
				break;
			write(1, "heredoc> ", 9);
			write(fdtemp[1], line, ft_strlen(line));
			write(fdtemp[1], "\n", 1);
			free (line);
			ret = get_next_line(0, &line);
		}
		free(line);
		fdin=fdtemp[0];
		close(fdtemp[1]);
	}
	ft_dup2(fdin, 0);
}

void	ft_redir_out(t_cmd commands, int *fdout)
{
	if (commands.output == out)
		*fdout = open(commands.outfile, O_WRONLY | O_TRUNC | O_CREAT | O_CLOEXEC, 0777);
	else if (commands.output == out_append)
		*fdout = open(commands.outfile, O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0777);
	if (*fdout < 0)
		perror("outfile failed to open");
	// printf("out: %d\n", *fdout);
}


/*
** Sample from purdue.edu pdf on pipes
** Set fds before forking child
** Child can read/write to/from STDIN/STDOUT
*/
void	ft_execute(t_commands cmds, t_list *env)
{
	int	fdstd[2];
	int fdpipe[2];
	int	fdnew[2];
	pid_t	pid;
	char	**envp;

	envp = ft_get_envp(env);
	fdstd[0] = dup(0);
	fdstd[1] = dup(1);
	fdnew[0] = dup(fdstd[0]);
	for (int i = 0; i < cmds.len; i++)
	{
		if (cmds.commands[i].input)
			ft_redir_in(cmds.commands[i], fdnew[0]);
		ft_dup2(fdnew[0], 0);
		if (i == cmds.len - 1)
		{
			if(cmds.commands[i].output)
				ft_redir_out(cmds.commands[i], &fdnew[1]);
			else 
				fdnew[1] = dup(fdstd[1]);
		}
		else
		{
			if (pipe(fdpipe) == -1) 
				perror("failed to create pipe");
			fdnew[1] = fdpipe[1];
			fdnew[0] = fdpipe[0];
		}
		ft_dup2(fdnew[1], 1);
		pid = fork();
		if (pid == 0)
		{
			execve(cmds.commands[i].args[0], cmds.commands[i].args, envp);
			printf("command not found: %s\n", cmds.commands[i].args[0]);
			exit (1);
		}
	}
	int child_status;
	int	exit_status;
	ft_dup2(fdstd[0], 0);
	ft_dup2(fdstd[1], 1);
	waitpid(pid, &child_status, 0);
	exit_status = WEXITSTATUS(child_status);
	printf("$?: %d\n", exit_status);
	ft_free_double_arr(envp);
}
