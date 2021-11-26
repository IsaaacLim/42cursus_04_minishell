#include "minishell.h"
#include "get_next_line.h"

/*
** Start program at argv[1] with arguments argv.
** Set up new stdin, stdout, stderr
** Puts reference to new process and pipes into `p`
** Reference: https://jameshfisher.com/2017/02/17/how-do-i-call-a-program-in-c-with-pipes/
** Combined with: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
*/
void	ft_fork(t_cmd commands, t_subprocess *p)
{
	char	**args;
	int		child_in[2];
	int		child_out[2];
	int		fd_pipe[2];
	pid_t	pid;

	args = commands.args;
	ft_create_pipe(child_in);
	ft_create_pipe(child_out);

	pid = fork();
	if (pid == -1)	
	{
		perror("Could not create fork");
		exit (1);
	}
	if (pid == 0) //child process
	{
		ft_fd_table_child(child_in, child_out);
		ft_redir_in(commands);
		ft_redir_out(commands);
		char *envp[] = {NULL};
		execve(args[0], args, envp);
		printf("command not found: %s\n", args[0]);
	}
	else
	{
		ft_fd_table_parent(child_in, child_out, p);
		p->pid = pid;
		ft_parent(args, p);
		//create close fd functions
	}
}

