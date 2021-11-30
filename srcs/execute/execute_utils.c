#include "minishell.h"
#include "environment.h"

/*
** dup2, error check, and close oldfd
*/
void	ft_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		perror("Could not duplicate(2) pipe end");
	else
		close(oldfd);
}

/*
** Converts envp stored in t_envar to a double arr
*/
char	**ft_get_envp(t_list *env)
{
	t_envar	*envar;
	char	**arr;
	int		lstsize;
	int		i;

	lstsize = ft_lstsize(env);
	arr = (char **)malloc(sizeof(char *) * (lstsize + 1));
	if (!arr)
		ft_libft_error("malloc failed in ft_get_envp");
	i = 0;
	while(i < lstsize && env)
	{
		envar = (t_envar *)env->content;
		arr[i] = ft_strjoin_bonus(envar->name, envar->word, '=');
		if (!arr[i])
			ft_libft_error("ft_strjoin_bonus failed in ft_get_envp");
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

/*
** Used to find PATH variable for execve()
*/
char	**split_path(t_list *env)
{
	t_envar *envar;

	envar = NULL;
	while (env)
	{
		envar = (t_envar *)(env->content);
		if (ft_strncmp(envar->name, "PATH", 5) == 0)
			break ;		
		env = env->next;
	}
	if (!envar)
		return (NULL);
	return (ft_split(envar->word, ':'));
}
