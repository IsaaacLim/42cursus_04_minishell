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
	char	*temp;
	int		lstsize;
	int		i;

	lstsize = ft_lstsize(env);
	arr = (char **)malloc(sizeof(char *) * lstsize + 1);
	i = 0;
	while(i < lstsize && env)
	{
		envar = (t_envar *)env->content;
		temp = ft_strjoin(envar->name, "=");
		arr[i] = ft_strjoin(temp, envar->word);
		free(temp);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
