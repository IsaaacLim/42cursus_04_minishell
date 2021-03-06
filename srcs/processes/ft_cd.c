/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:14:15 by jinlim            #+#    #+#             */
/*   Updated: 2021/12/02 14:39:06 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

static int	ft_chdir(char *dir, t_list *env)
{
	char	pwd[PATH_MAX];
	char	*pwd_env;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		ft_perror_exit("getcwd failed in ft_cd");
	if (chdir(dir) != 0)
	{
		printf("cd: No such file or directory: %s\n", dir);
		return (1);
	}
	else
	{
		pwd_env = ft_strjoin("OLDPWD=", pwd);
		export_add(&env, pwd_env);
		free(pwd_env);
		if (getcwd(pwd, sizeof(pwd)) == NULL)
			ft_perror_exit("getcwd failed in ft_cd");
		pwd_env = ft_strjoin("PWD=", pwd);
		export_add(&env, pwd_env);
		free(pwd_env);
		return (0);
	}
}

static int	ft_cd_oldpwd(t_list *env)
{
	t_list	*found;
	char	*old_pwd;
	int		exit_status;

	exit_status = 1;
	found = found_env(&env, NULL, "OLDPWD", INT_MAX);
	if (found)
	{
		old_pwd = ((t_envar *)(found->content))->word;
		printf("%s\n", old_pwd);
		exit_status = ft_chdir(old_pwd, env);
	}
	else
		printf("cd: OLDPWD not set\n");
	return (exit_status);
}

int	ft_cd(char **argv, t_list *env)
{
	t_list	*found;
	char	*home;
	int		exit_status;

	exit_status = 1;
	found = found_env(&env, NULL, "HOME", INT_MAX);
	home = ((t_envar *)(found->content))->word;
	if (!argv[1])
		exit_status = ft_chdir(home, env);
	else if (!argv[2])
	{
		if (!ft_strncmp(argv[1], "-", 2))
			exit_status = ft_cd_oldpwd(env);
		else
			exit_status = ft_chdir(argv[1], env);
	}
	else if (argv[2])
		printf("cd: too many arguments\n");
	return (exit_status);
}
