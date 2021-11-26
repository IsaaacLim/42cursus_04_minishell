#include "minishell.h"

void	ft_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("Could not duplicate(2) pipe end");
		exit (1);
	}
	close(oldfd);
}

void	ft_create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("Could not create pipe");
		exit (1);
	}
}

int	**ft_pipefd(int cmds_len)
{
	int	**pipefd;
	int	i;

	pipefd = (int **)malloc(sizeof(int *) * (cmds_len - 1));
	if (!pipefd)
	{
		perror("pipefd ** fail");
		exit(1);
	}
	i = 0;
	while (i < cmds_len - 1)
	{
		pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipefd[i])
		{
			perror("pipefd * fail");
			exit (1);
		}
		ft_create_pipe(pipefd[i]);
		i++;
	}
	return (pipefd);
}
