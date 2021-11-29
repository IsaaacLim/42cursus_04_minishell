#include "minishell.h"
#include "environment.h"

/*
** Child process execute commands
** If invalid command, return 1 to parent
*/
static void	ft_child_process(char **args, char **envp, t_list *env)
{
	int	exit_status;

	exit_status = 0;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	sleep(1);
	if (!ft_strncmp(args[0], "env", 4))
		exit_status = ft_display_env(env, args);
	else if (!ft_strncmp(args[0], "export", 7))
		export_command(env);
	else
	{
		execve(args[0], args, envp);
		printf("command not found: %s\n", args[0]);
		exit (127);
	}
	exit (exit_status);
}

/*
** Restore STDIN/OUT fd
** Wait for child process (only last) to complete
** Stores the exit status of the last command
*/
static void	ft_parent_process(int fdstd[2], int pid, char **envp)
{
	int child_status;
	int	wifexited;
	int	wifsignaled;
	int	wtermsig;
	int wexitstatus;

	signal(SIGINT, SIG_IGN);
	ft_dup2(fdstd[0], 0);
	ft_dup2(fdstd[1], 1);
	waitpid(pid, &child_status, 0);
	wifexited = WIFEXITED(child_status);
	wifsignaled = WIFSIGNALED(child_status);
	wtermsig = WTERMSIG(child_status);
	wexitstatus = WEXITSTATUS(child_status);
	if (wifexited)
		g_exit_status = wexitstatus;
	else if (wifsignaled)
	{
		if (wtermsig == 2)
			printf("\n");
		else if(wtermsig == 3)
			printf("msh: quit\n");
		g_exit_status = wtermsig + 128;
	}
	else
		g_exit_status = -1;
	ft_free_double_arr(envp);
}

/*
** Sample from purdue.edu pdf on pipes
** Set fds before forking child
** Child can read/write to/from STDIN/STDOUT
*/
void	ft_execute(t_commands cmds, t_list *env)
{
	int	fdstd[2];
	int fdpipe[2];
	int	fdnew[2];
	pid_t	pid;
	char	**envp;
	int	i;

	envp = ft_get_envp(env);
	fdstd[0] = dup(0);
	fdstd[1] = dup(1);
	fdnew[0] = dup(fdstd[0]);
	i = 0;
	while (i < cmds.len)
	{
		ft_redir_in(cmds.commands[i], &fdnew[0]);
		if (i == cmds.len - 1)
			ft_redir_out(cmds.commands[i], &fdnew[1], fdstd[1]);
		else
			ft_redir_pipe(fdnew, fdpipe);
		ft_dup2(fdnew[1], 1);
		pid = fork();
		if (pid == 0)
			ft_child_process(cmds.commands[i].args, envp, env);
		i++;
	}
	ft_parent_process(fdstd, pid, envp);
}
