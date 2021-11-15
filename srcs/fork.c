#include "minishell.h"
#include "get_next_line.h"

void	ft_mod_fd(int fd_to, int fd_from)
{
	if (dup2(fd_to, fd_from) == -1)
	{
		perror("Could not duplicate pipe end");
		exit (1);
	}
	close(fd_to);
}

void	ft_make_pipe(int fds[2])
{
	if (pipe(fds) == -1)
	{
		perror("Could not create pipe");
		exit (1);
	}
}

/*
** fd: 0 = Read; 1 = Write
** child_in is to be Read
** child_out is to be Written
** Then replace STDIN/OUT with child pipe fd
*/
void	ft_fd_table_child(int child_in[2], int child_out[2])
{
	close (0);
	close (1);
	close (child_in[1]);
	close (child_out[0]);
	ft_mod_fd(child_in[0], 0);
	ft_mod_fd(child_out[1], 1);
}

/*
** Parent may write to subprocess child_in
** Parent may read from subprocess child_out
*/
void	ft_fd_table_parent(int *child_in, int *child_out, t_subprocess *p)
{
	close (child_in[0]);
	close (child_out[1]);
	p->fd_to_child = child_in[1];
	p->fd_from_child = child_out[0];
}

void	ft_getnextline(t_subprocess *p)
{
	char	*line;
	int		ret;
	// char buf[30];
	
	ret = get_next_line(p->fd_from_child, &line);
	while (ret > 0)
	{
		printf("Parent read: %s\n", line);
		free(line);
		ret = get_next_line(p->fd_from_child, &line);
	}
	free(line);
	if (ret == -1)
	{
		printf("Fail to get_next_line\n");
		exit(1);
	}
}

/*
** Start program at argv[1] with arguments argv.
** Set up new stdin, stdout, stderr
** Puts reference to new process and pipes into `p`
** Reference: https://jameshfisher.com/2017/02/17/how-do-i-call-a-program-in-c-with-pipes/
*/
void	ft_fork(char *argv[], t_subprocess *p)
{
	int		child_in[2];
	int		child_out[2];
	pid_t	pid;

	ft_make_pipe(child_in);
	ft_make_pipe(child_out);
	pid = fork();
	if (pid == -1)	
	{
		perror("Could not create fork");
		exit (1);
	}
	if (pid == 0) //child process
	{
		ft_fd_table_child(child_in, child_out);
		char *envp[] = {NULL};
		execve(argv[0], argv, envp);
		printf("command not found: %s\n", argv[0]);
	}
	else
	{
		ft_fd_table_parent(child_in, child_out, p);
		p->pid = pid;

		int	child_status;
		waitpid(p->pid, &child_status, 0);
		printf("%i\n", WEXITSTATUS(child_status)); //needs to be stored for the next child process
	
		ft_getnextline(p); //for display functions

		//create close fd functions
	}
}
