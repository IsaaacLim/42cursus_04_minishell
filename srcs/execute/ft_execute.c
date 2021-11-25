#include "minishell.h"
#include "get_next_line.h"

/*
** Sample programs to test pipes
** Each additional cmds->len will add 5 to total output
*/
void	ft_execute_sample_child()
{
	int y;
	read(0, &y, sizeof(int));
	y += 5;
	write(1, &y, sizeof(int));
}
void	ft_execute_sample_parent(int child_in[2])
{
	int y = 10;
	write(child_in[1], &y, sizeof(int));
	read(0, &y, sizeof(int));
	close(0);
	printf("final x: %d\n", y);
}

/*
** Child fd table (initial)
** Read from child_in[0]
** Write to child_out[1]
*/
void	ft_fd_table_child(int child_in[2], int child_out[2])
{
	close (0);
	close (1);
	close (child_in[1]);
	close (child_out[0]);
	ft_dup2(child_in[0], 0);
	ft_dup2(child_out[1], 1);
}

/*
** Parent fd table
** Read from child_out[0]
*/
void	ft_fd_table_parent(int *child_in, int *child_out)
{
	close (child_in[0]);
	close (child_out[1]);
	ft_dup2(child_out[0], 0);
}

/*
** Parent function
**	Wait for child process to complete
**	Reads output from child and write to STDOUT
*/
void	ft_parent(pid_t pid)
{
	char	*line;
	int		child_status;
	int		ret;

	waitpid(pid, &child_status, 0); //store this somewhere for next echo to access
	// printf("$?: %i\n", WEXITSTATUS(child_status));
	ret = get_next_line(0, &line);
	while (ret > 0)
	{
		printf("Parent read: %s\n", line);
		free(line);
		ret = get_next_line(0, &line);
	}
	free(line);
	if (ret == -1)
	{
		printf("Fail to get_next_line\n");
		exit(1);
	}
}

void	ft_execute(t_commands cmds)
{
	int		child_in[2];
	int		child_out[2];
	int		**pipefd;
	int		i;
	pid_t	pid;

	t_cmd	commands;
	t_subprocess p;
	char	**args;
	
	ft_create_pipe(child_in);
	ft_create_pipe(child_out);
	if (cmds.len > 1)
		pipefd = ft_pipefd(cmds.len);
	i = 0;
	while(i < cmds.len)
	{
		commands = cmds.commands[i];
		args = commands.args;
		pid = fork();
		if (pid == -1)	
		{
			perror("Could not create fork");
			exit (1);
		}
		if (pid == 0)
		{
			ft_fd_table_child(child_in, child_out);
			// ft_redir_in(commands);
			// ft_redir_out(commands);
			ft_redir_pipe(cmds.len, i, pipefd);
			char *envp[] = {NULL};
			// close (0);
			execve(args[0], args, envp);
			// ft_execute_sample_child();
			printf("command not found: %s\n", args[0]);
			return ; 
		}
		i++;
	}
	int tmpin = dup(0);
	ft_fd_table_parent(child_in, child_out);
	ft_parent(pid);
	// ft_execute_sample_parent(child_in);
	ft_dup2(tmpin, 0);
	i = 0;
	while (i < cmds.len - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		free(pipefd[i]);
		i++;
	}
	if (cmds.len > 1)
		free(pipefd);
	close (child_in[1]);
}
