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

void	ft_exit_status(unsigned char exit_status)
{
	int		status_len;
	char	*ptr;

	if (exit_status >= 100)
		status_len = 3;
	else if (exit_status >= 10)
		status_len = 2;
	else
		status_len = 1;
	g_exstat.exit_status = exit_status;
	g_exstat.env->word_len = status_len;
	ptr = g_exstat.env->word;
	ptr[status_len] = '\0';
	while (--status_len >= 0)
	{
		ptr[status_len] = (exit_status % 10) + '0';
		exit_status /= 10;
	}
}
