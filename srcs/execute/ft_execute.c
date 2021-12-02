/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:13:42 by jinlim            #+#    #+#             */
/*   Updated: 2021/12/02 14:35:29 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_execve(char **args, char **envp, t_list *env)
{
	char	**path_arr;
	char	*new_path;
	int		i;

	execve(args[0], args, envp);
	new_path = ft_strjoin_bonus(getenv("PWD"), args[0], "/srcs/built_ins/");
	if (!new_path)
		ft_libft_error("ft_strjoin_bonus failed in ft_execve");
	execve(new_path, args, envp);
	free(new_path);
	path_arr = split_path(env);
	if (!path_arr)
		ft_libft_error("split_path failed in ft_execve");
	i = 0;
	while (path_arr[i])
	{
		new_path = ft_strjoin_bonus(path_arr[i], args[0], "/");
		if (!new_path)
			ft_libft_error("ft_strjoin_bonus failed in ft_execve");
		execve(new_path, args, envp);
		free(new_path);
		i++;
	}
	ft_free_double_arr(path_arr);
}

/*
** Child process execute commands
** If invalid command, return 1 to parent
*/
static void	ft_child_process(char **args, t_list *env)
{
	char	**envp;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	envp = ft_get_envp(env);
	ft_execve(args, envp, env);
	printf("msh: command not found: %s\n", args[0]);
	ft_free_double_arr(envp);
	exit (127);
}

/*
** Restore STDIN/OUT fd
** Wait for child process (only last) to complete
** Stores the exit status of the last command
*/
static void	ft_parent_process(int fdstd[2], int *pid, int cmds_len)
{
	int	child_status;
	int	wtermsig;
	int	wexitstatus;
	int	i;

	signal(SIGINT, SIG_IGN);
	ft_dup2(fdstd[0], 0);
	ft_dup2(fdstd[1], 1);
	i = -1;
	while (++i < cmds_len)
		waitpid(pid[i], &child_status, 0);
	wexitstatus = WEXITSTATUS(child_status);
	wtermsig = WTERMSIG(child_status);
	if (WIFEXITED(child_status))
		ft_exit_status(wexitstatus);
	else if (WIFSIGNALED(child_status))
	{
		if (wtermsig == 2)
			printf("\n");
		else if (wtermsig == 3)
			printf("msh: quit\n");
		ft_exit_status(wtermsig + 128);
	}
	free(pid);
}

/*
** Sample from purdue.edu pdf on pipes
** Set fds before forking child
** Child can read/write to/from STDIN/STDOUT
*/
void	ft_execute(t_commands cmds, t_list *env)
{
	int		fdstd[2];
	int		fdpipe[2];
	int		fdnew[2];
	pid_t	*pid;
	int		i;

	fdstd[0] = dup(0);
	fdstd[1] = dup(1);
	fdnew[0] = dup(fdstd[0]);
	pid = (pid_t *)malloc(sizeof(pid_t) * cmds.len);
	i = -1;
	while (++i < cmds.len)
	{
		ft_redir_in(cmds.commands[i], &fdnew[0]);
		if (i == cmds.len - 1)
			ft_redir_out(cmds.commands[i], &fdnew[1], fdstd[1]);
		else
			ft_redir_pipe(fdnew, fdpipe);
		ft_dup2(fdnew[1], 1);
		pid[i] = fork();
		if (pid[i] == 0)
			ft_child_process(cmds.commands[i].args, env);
	}
	ft_parent_process(fdstd, pid, cmds.len);
}
