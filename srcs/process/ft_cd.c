#include "minishell.h"
#include "environment.h"

static void	ft_getcwd(char **cwd)
{
	if (getcwd(*cwd, sizeof(*cwd)) == NULL)
		ft_perror("getcwd failed in ft_cd");
}

static void	ft_chdir(char *dir, t_list *env)
{
	char	pwd[PATH_MAX];
	char	*pwd_env;

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		ft_perror("getcwd failed in ft_cd");
	if (chdir(dir) != 0)
		printf("cd: No such file or directory: %s\n", dir);
	else
	{
		pwd_env = ft_strjoin("OLDPWD=", pwd);
		export_add(&env, pwd_env);
		free(pwd_env);
		if (getcwd(pwd, sizeof(pwd)) == NULL)
			ft_perror("getcwd failed in ft_cd");
		pwd_env = ft_strjoin("PWD=", pwd);
		export_add(&env, pwd_env);
		free(pwd_env);
		g_exit_status = 0;
	}
}

static void	ft_cd_home(char *argv, char *home, t_list *env)
{
	char	*join_home;

	if (!ft_strncmp(argv, "~", 2) || !ft_strncmp(argv, "~/", 3))
		ft_chdir(home, env);
	else if(!ft_strncmp(argv, "~/", 2))
	{
		join_home = ft_strjoin(home, ++argv);
		ft_chdir(join_home, env);
		free(join_home);
	}
	else
		ft_chdir(argv, env);
}

static void ft_cd_oldpwd(t_list *env)
{
	t_list	*found;
	char	*old_pwd;

	found = found_env(&env, NULL, "OLDPWD", INT_MAX);
	if (found)
	{
		old_pwd = ((t_envar *)(found->content))->word;
		printf("%s\n", old_pwd);
		ft_chdir(old_pwd, env);
	}
	else
		printf("cd: OLDPWD not set\n");
	
}

void	ft_cd(char **argv, t_list *env)
{
	t_list	*found;
	char	*home;

	g_exit_status = 1;
	if (argv[2])
	{
		printf("cd: too many arguments\n");
		return ;
	}
	found = found_env(&env, NULL, "HOME", INT_MAX);
	home = ((t_envar *)(found->content))->word;
	if (!argv[1])
		ft_chdir(home, env);
	else if (!argv[2])
	{
		if (argv[1][0] == '~')
			ft_cd_home(argv[1], home, env);
		else if (!ft_strncmp(argv[1], "-", 2))
			ft_cd_oldpwd(env);
		else
			ft_chdir(argv[1], env);
	}
}
