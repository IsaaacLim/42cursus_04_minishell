#include "minishell.h"

void	ft_mod_fd(int fd_to, int fd_from)
{
	if (dup2(fd_to, fd_from) == -1)
		perror("Could not duplicate pipe end"); //need exit?
	close(fd_to);
}

void	ft_make_pipe(int fds[2])
{
	if (pipe(fds) == -1)
	{
		perror("Could not create pipe");
		exit (1); //need exit?
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
	int		child_err[2];
	pid_t	pid;

	ft_make_pipe(child_in);
	ft_make_pipe(child_out);
	// ft_make_pipe(child_err);
	pid = fork();
	if (pid == -1)	
		perror("Could not create fork"); //need exit?
	if (pid == 0) //child process
	{
		close (0);
		close (1);
		// close (2); //close parent pipes
		close (child_in[1]); //close child stdin (write)
		close (child_out[0]); //close child stdout (read)
		close (child_err[0]); //close child stderr (read)
		ft_mod_fd(child_in[0], 0); //child stdin (read) -> STDIN_FILENO
		ft_mod_fd(child_out[1], 1); //child stdout (write) -> STDOUT_FILENO
		// ft_mod_fd(child_err[1], 2); //child stderr (write) -> STDERR_FILENO
		char *envp[] = {NULL};
		execve(argv[1], argv, envp);
		printf("Didn't work\n");
	}
	else
	{
		close (child_in[0]); //close child stdin (read)
		close (child_out[1]); //close child stdin (write)
		// close (child_err[1]); //close child stderr (write)
		p->pid = pid;
		p->stdin = child_in[1]; //parent write to subprocess child_in
		p->stdout = child_out[0]; //parent read from subprocess child_out
		// p->stderr = child_err[0]; //parent read from subprocess child_err

		char buf[44];
		if (read(p->stdout, buf, 44) == -1)
			perror("Could not read");
		printf("Parent read: %s\n", buf);
		wait(NULL);
	}
}
