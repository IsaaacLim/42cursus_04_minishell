#include "minishell.h"
#include "get_next_line.h"

int	ft_heredoc(char *infile, int stdfd[2])
{
	char	*line;
	int		ret;
	int		tmpfd[2];

	ft_dup2(stdfd[0], 0);
	ft_dup2(stdfd[1], 1);
	ft_create_pipe(tmpfd);
	write(1, "heredoc> ", 9);
	ret = get_next_line(0, &line);
	while (ret > 0)
	{
		if (!ft_strncmp(line, infile, ft_strlen(infile) + 1))
			break;
		write(1, "heredoc> ", 9);
		write(tmpfd[1], line, ft_strlen(line));
		write(tmpfd[1], "\n", 1);
		free(line);
		ret = get_next_line(0, &line);
	}
	free(line);
	close(tmpfd[1]);
	return(tmpfd[0]);
}

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