#include "minishell.h"
#include "get_next_line.h"

void	ft_store_fd(int temp_fd, int std_fd)
{
	temp_fd = dup(std_fd);
	if (temp_fd == -1)
	{
		perror("Could not duplicate pipe end");
		exit (1);
	}
}

void	ft_mod_fd(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("Could not duplicate(2) pipe end");
		exit (1);
	}
	close(oldfd);
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
** Child function
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
** Child function
** Redirections
** TO DO: Close the files
*/
void	ft_fd_table_redir(t_cmd commands)
{
	int	fd_new;

	if (commands.input == in)
	{
		fd_new = open(commands.infile, O_RDONLY | O_CLOEXEC, 0777);
		if (fd_new < 0)
		{
			perror("failed to open");
			exit(1);
		}
		ft_mod_fd(fd_new, 0);
	}
	if (commands.output)
	{
		if (commands.output == out)
			fd_new = open(commands.outfile, O_WRONLY | O_TRUNC | O_CREAT | O_CLOEXEC, 0777);
		else if (commands.output == out_append)
			fd_new = open(commands.outfile, O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0777);
		if (fd_new < 0)
		{
			perror("failed to open");
			exit(1);
		}
		ft_mod_fd(fd_new, 1);
	}
}

void	ft_fd_table_redir_in(t_cmd commands, int fd_pipe_in, bool is_first_cmd)
{
	int fd_new;

	fd_new = 0;
	if (!is_first_cmd)
	{
		fd_new = fd_pipe_in;
		printf("pipe in fd: %d\n", fd_new);
	}
	else if (commands.input == in)
	{
		fd_new = open(commands.infile, O_RDONLY | O_CLOEXEC, 0777);
		if (fd_new < 0)
		{
			perror("failed to open");
			exit(1);
		}
	}
	if (fd_new)
		ft_mod_fd(fd_new, 0);
}

void	ft_fd_table_redir_out(t_cmd commands, int fd_pipe_out, bool is_last_cmd)
{
	int	fd_new;

	fd_new = 0;
	if (!is_last_cmd)
	{
		fd_new = fd_pipe_out;
		printf("pipe out fd: %d\n", fd_new);
	}
	else if (commands.output)
	{
		if (commands.output == out)
			fd_new = open(commands.outfile, O_WRONLY | O_TRUNC | O_CREAT | O_CLOEXEC, 0777);
		else if (commands.output == out_append)
			fd_new = open(commands.outfile, O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0777);
		if (fd_new < 0)
		{
			perror("failed to open");
			exit(1);
		}
	}
	if (fd_new)
		ft_mod_fd(fd_new, 1);
	
}
/*
** Redirects IN/OUT if pipe is present (not last command)
*/
void	ft_fd_table_pipe(int *fd_pipe, bool first_command, bool last_command)
{
	ft_mod_fd(fd_pipe[0], 0);
	ft_mod_fd(fd_pipe[1], 1);
}

/*
** Parent function
** Parent may write to subprocess child_in
** Parent may read from subprocess child_out
*/
void	ft_fd_table_parent(int *child_in, int *child_out, t_subprocess *p)
{
	close (child_in[0]);
	close (child_out[1]);
	p->fd_to_child = child_in[1];
	p->fd_from_child = child_out[0];
	printf("parent - to child: %d\n", child_in[1]); //temp
	printf("parent - from child: %d\n", child_in[0]); //temp
}

/*
** Parent function
** Reads and prints from child_out
*/
void	ft_getnextline(t_subprocess *p)
{
	char	*line;
	int		ret;
	
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
** Parent function cont'd
*/
void	ft_parent(char *argv[], t_subprocess *p)
{
	int	child_status;

	waitpid(p->pid, & child_status, 0); //store this somewhere for next echo to access
	printf("$?: %i\n", WEXITSTATUS(child_status));
	ft_getnextline(p); //for display functions
}

/*
** Start program at argv[1] with arguments argv.
** Set up new stdin, stdout, stderr
** Puts reference to new process and pipes into `p`
** Reference: https://jameshfisher.com/2017/02/17/how-do-i-call-a-program-in-c-with-pipes/
** Combined with: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
*/
void	ft_fork(t_cmd commands, t_subprocess *p, bool is_first_cmd, bool is_last_cmd)
{
	char	**args;
	int		std_fd[2];
	int		child_in[2];
	int		child_out[2];
	int		fd_pipe[2];
	pid_t	pid;

	args = commands.args;
	ft_store_fd(std_fd[0], 0);
	ft_store_fd(std_fd[1], 1); //haven't used it
	ft_make_pipe(child_in);
	ft_make_pipe(child_out);
	ft_make_pipe(fd_pipe);
	//set redirections here

	//run fork for num of commands
	//for (int i = 0; i < n_commands, i++)
	pid = fork();
	if (pid == -1)	
	{
		perror("Could not create fork");
		exit (1);
	}
	if (pid == 0) //child process
	{
		ft_fd_table_child(child_in, child_out);
		ft_fd_table_redir_in(commands, fd_pipe[0], is_first_cmd);
		ft_fd_table_redir_out(commands, fd_pipe[1], is_last_cmd);
		// if (commands.input || commands.output) //this is fine
			// ft_fd_table_redir(commands);
		// ft_fd_table_pipe(fd_pipe, first_command, last_command); //doesn't work
		if (is_last_cmd)
			printf("last out fd: %d\n", child_out[1]);
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

void	ft_execute3(t_commands *cmds)
{
	int	tmpin = dup(0);
	int	tmpout = dup(1);

	int child_in[2];
	int child_out[2];

	child_in[0] = dup(tmpin);

	int fdpipe[2];
	pipe(fdpipe);

	int	ret;
	for (int i = 0; i < cmds->len; i++)
	{
		if (cmds->commands[i].input == in)
		{
			child_in[0] = open(cmds->commands[i].infile, O_RDONLY | O_CLOEXEC, 0777);
			if (child_in[0] < 0)
				perror("child_in[0] open");
		}
		dup2(child_in[0], 0);
		close(child_in[0]);
		if (i == cmds->len - 1)
		{
			if (cmds->commands[i].output)
			{
				child_out[1] = open(cmds->commands[i].outfile, O_WRONLY | O_TRUNC | O_CREAT | O_CLOEXEC, 0777);
				if (child_out[1] < 0)
					perror("child_in[1] open");
			}
			else
				child_out[1] = dup(tmpout);
			// dup2(child_out[1],1);
			// close(child_out[1]);
		}
		else
		{
			child_out[1] = fdpipe[1];
			child_in[0] = fdpipe[0];
		}
		dup2(child_out[1],1);
		close(child_out[1]);

		ret = fork();
		if (ret == 0)
		{	
			//doesn't work like this
			// if (i != cmds->len - 1)
			// {
			// 	child_out[1] = fdpipe[1];
			// 	child_in[0] = fdpipe[0];
			// 	dup2(child_out[1],1);
			// 	close(child_out[1]);
			// }

			// close (1);
			char *envp[] = {NULL};
			execve(cmds->commands[i].args[0], cmds->commands[i].args, envp);
			printf("command not found: %s\n", cmds->commands[i].args[0]);
			exit (1);
		}
	}

	// t_subprocess *p;

	// p->fd_from_child = child_out[1];
	// ft_getnextline(p);
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	waitpid(ret, NULL, 0);
}
