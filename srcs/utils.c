#include "minishell.h"

void	ft_free_double_arr(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		i++;
	while (--i >= 0)
	{
		ft_bzero(arr[i], ft_strlen(arr[i]));
		free(arr[i]);
	}
	free(arr);
	return ;
}

void	ft_exit_status(int exit_status)
{
	g_exstat.exit_status = exit_status;
}
