#include "minishell.h"

/*
** For child process
** Redirect input from input file / heredoc rather than child_in[0]
*/
void	ft_redir_in(t_cmd commands, int stdfd[2])
{
	int fd_new;

	if (!commands.input)
		return;
	if (commands.input == in)
	{
		fd_new = open(commands.infile, O_RDONLY | O_CLOEXEC, 0777);
		if (fd_new < 0)
		{
			perror("infile failed to open");
			exit(1);
		}
	}	
	else if (commands.input == in_heredoc)
		fd_new = ft_heredoc(commands.infile, stdfd);
	ft_dup2(fd_new, 0);
}

/*
** For child process
** Redirect output to file rather than child_out[1]
*/
void	ft_redir_out(t_cmd commands)
{
	int	fd_new;

	if (!commands.output)
		return ;
	if (commands.output == out)
		fd_new = open(commands.outfile, O_WRONLY | O_TRUNC | O_CREAT | O_CLOEXEC, 0777);
	else if (commands.output == out_append)
		fd_new = open(commands.outfile, O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0777);
	if (fd_new < 0)
	{
		perror("failed to open");
		exit(1);
	}
	ft_dup2(fd_new, 1);
}

/*
** For child process
** Redirect In/Out between multiple commands
*/
void	ft_redir_pipe(int len, int n, int **pipefd)
{
	if (n == 0 && len > 1) //pull this condition out
	{
		ft_pipe_out(n, pipefd);
		ft_pipe_close(len, n , pipefd); //put them all out
	}
	else if (n > 0 && n < len - 1)
	{
		ft_pipe_out(n, pipefd);
		ft_pipe_in(n, pipefd);
		ft_pipe_close(len, n, pipefd);
	}
	else if (n == len - 1 && len > 1)
	{
		ft_pipe_close(len, n, pipefd);
		ft_pipe_in(n, pipefd);
	}
}
