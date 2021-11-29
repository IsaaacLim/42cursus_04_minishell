#include "minishell.h"
#include "environment.h"

static void	ft_chdir(char *dir)
{
	if (chdir(dir) != 0)
		printf("cd: No such file or directory: %s\n", dir);
	else
		g_exit_status = 0;
}

int	ft_cd(char **argv, t_list *env)
{
	t_list	*found;
	char	*home;
	char	*join_home;

	g_exit_status = 1;
	found = found_env(&env, NULL, "HOME", INT_MAX);
	home = ((t_envar *)(found->content))->word;
	if (!argv[1])
		ft_chdir(home);
	else if (!argv[2])
	{
		if (!ft_strncmp(argv[1], "~", 2) || !ft_strncmp(argv[1], "~/", 3))
			ft_chdir(home);
		else if(!ft_strncmp(argv[1], "~/", 2))
		{
			join_home = ft_strjoin(home, &argv[1][1]);
			ft_chdir(join_home);
			free(join_home);
		}
		else
			ft_chdir(argv[1]);
	}
	else
		printf("cd: too many argumnets\n");
}
