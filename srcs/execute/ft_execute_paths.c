#include "minishell.h"
#include "environment.h"

/*
*	strjoin used to add a frontslash (/) in between
*	to avoid calling strjoin twice
*	used primarily to join path variable
*/
static char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = malloc(sizeof(char) * (len + 1 + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (*s1)
	{	
		tmp[i] = *s1++;
		i++;
	}
	tmp[i] = '/';
	i++;
	while (*s2)
	{
		tmp[i] = *s2++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

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

bool	ft_execve(char *cmd, char **args, char **envp, t_list *env)
{
	char **path_arr;
	int i;
	char *new_path;

    // attempt execution from relative path
    execve(cmd, args, envp);
	// attempt execution from exiting PATH
	new_path = ft_strjoin2("srcs/built_ins", cmd);
	execve(new_path, args, envp);
	free(new_path);
	path_arr = split_path(env);
	i = 0;
	if (!path_arr)
		return (false);
	while (path_arr[i][0])
	{
		new_path = ft_strjoin2(path_arr[i], cmd);
		execve(new_path, args, envp);
		free(new_path);
		i++;
	}
	ft_free_double_arr(path_arr);
	return (false);
}