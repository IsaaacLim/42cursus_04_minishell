#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

void	ft_romanian(void)
{
	int pipefd[2][2];
	int	i;
	int y;

	i = 0;
	while (i < 2)
	{
		pipe(pipefd[i]);
		i++;
	}
	int pid1 = fork();
	if (pid1 == 0)
	{
		close (0);
		close (1);
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		dup2(pipefd[0][0], 0);
			close (pipefd[0][0]);
		dup2(pipefd[1][1], 1);
			close(pipefd[1][1]);
		read(0, &y, sizeof(int));
		y += 7;
		write(1, &y, sizeof(int));
		close(0);
		close(1);
		return ;
	}

	close(pipefd[0][0]);
	close(pipefd[1][1]);
	dup2(pipefd[1][0], 0);
	close (pipefd[1][0]);
	y = 10;
	write(pipefd[0][1], &y, sizeof(int));
	read(0, &y, sizeof(int));
	close(0);
	printf("final x: %d\n", y);
	waitpid(pid1, NULL, 0);
}

void	ft_fd_table_child(int child_in[2], int child_out[2])
{
	close (0);
	close (1);
	close(child_in[1]);
	close(child_out[0]);
	dup2(child_in[0], 0);
		close (child_in[0]);
	dup2(child_out[1], 1);
		close(child_out[1]);
}

void	ft_execute()
{
	int y;
	read(0, &y, sizeof(int));
	y += 5;
	write(1, &y, sizeof(int));

}

void	ft_fd_table_parent(int *child_in, int *child_out)
{
	close(child_in[0]);
	close(child_out[1]);
	dup2(child_out[0], 0);
	close (child_out[0]);
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

void	ft_pipe(int len, int n, int **pipefd)
{
	//len = 3;

	if (n == 0)
	{
		ft_pipe_out(n, pipefd);
		close(pipefd[1][0]);
		close(pipefd[1][1]);
	}

	if (n > 0 && n < len - 1)
	{
		ft_pipe_in(n, pipefd);
		ft_pipe_out(n, pipefd);
	}

	if (n == len - 1)
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);

		ft_pipe_in(n, pipefd);
	}
}

void	ft_mine(void)
{
	int child_in[2]; //pipefd[0]
	int child_out[2]; //pipefd[1]
	int	i;
	int y;


	pipe(child_in);
	pipe(child_out);

	int len = 4;
	int	**pipefd;
	pipefd = (int **)malloc(sizeof(int *) * len - 1);
	i = 0;
	while (i < len - 1)
	{
		pipefd[i] = (int *)malloc(sizeof(int));
		pipe(pipefd[i]);
		i++;
	}

	int pid;
	i = 0;
	while (i < len)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_fd_table_child(child_in, child_out);

			//pipe
			ft_pipe(len, i, pipefd);

			ft_execute();
			close(0);
			close(1);
			return ;
		}
		i++;
	}
	ft_fd_table_parent(child_in, child_out);
	y = 10;
	write(child_in[1], &y, sizeof(int));
	read(0, &y, sizeof(int));
	close(0);
	printf("final x: %d\n", y);
	waitpid(pid, NULL, 0);
	i = 0;
	while (i < len - 1)
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
}

int	main(void)
{
	// ft_romanian();
	ft_mine();
}
