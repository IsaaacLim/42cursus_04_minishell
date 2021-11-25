#include "minishell.h"

void	ft_pipe_out(int n, int **pipefd)
{
	close(pipefd[n][0]);
	dup2(pipefd[n][1], 1);
		close(pipefd[n][1]);
}

void	ft_pipe_in(int n, int **pipefd)
{
	close(pipefd[n - 1][1]);
	dup2(pipefd[n - 1][0], 0);
		close(pipefd[n - 1][0]);

}

void	ft_pipe_close(int len, int n, int **pipefd)
{
	int i;

	i = 0;
	while (i < len - 1)
	{
		if (n == 0)
		{
			if (i + 1 < len - 1)
			{
				close(pipefd[i + 1][0]);
				close(pipefd[i + 1][1]);
			}
		}
		else if (n > 0 && n < len - 1)
		{
			if (i + 1 < n || i > n)
			{
				close(pipefd[i][0]);
				close(pipefd[i][1]);
			}
		}
		else if (n == len - 1)
		{
			if (i < n - 1)
			{
				close(pipefd[i][0]);
				close(pipefd[i][1]);
			}
		}
		i++;
	}
}
