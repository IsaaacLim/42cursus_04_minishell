/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:59:32 by jinlim            #+#    #+#             */
/*   Updated: 2021/12/01 20:27:34 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static char	*ft_strdup(const char *s1)
{
	int		len;
	char	*dst;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	dst = (char *)malloc(len * sizeof(char) + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	ft_sort_envp(char **envp, int envp_len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < envp_len)
	{
		j = i + 1;
		while (j < envp_len)
		{
			if (ft_strncmp(envp[i], envp[j], INT_MAX) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[j];
				envp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_display(char **tmp_arr)
{
	int	i;
	int	j;

	i = -1;
	while (tmp_arr[++i])
	{
		printf("%s", tmp_arr[i]);
		j = 0;
		while (tmp_arr[i][j])
			j++;
		if (tmp_arr[i][j - 1] == '=')
			printf("''");
		printf("\n");
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char	**tmp_arr;
	int		ori_len;
	int		new_len;
	int		i;

	ori_len = 0;
	while (envp[ori_len])
		ori_len++;
	tmp_arr = (char **)malloc(sizeof(char *) * (ori_len + 1));
	if (!tmp_arr)
		perror("malloc failed in export.c");
	i = -1;
	new_len = 0;
	while (envp[++i])
	{
		if (envp[i][0] == '?' && envp[i][1] == '=')
			continue ;
		tmp_arr[new_len] = ft_strdup(envp[i]);
		new_len++;
	}
	tmp_arr[new_len] = NULL;
	ft_sort_envp(tmp_arr, new_len);
	ft_display(tmp_arr);
	free (tmp_arr);
	return (0);
}
