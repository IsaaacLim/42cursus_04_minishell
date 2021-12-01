/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:50:11 by jkhong            #+#    #+#             */
/*   Updated: 2021/12/01 20:59:36 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "parser.h"

static int	return_env_len(char *str, t_list **env)
{
	int			tot_len;
	int			env_len;
	t_envar		*envar;
	static char	quote = 0;

	tot_len = 0;
	while (*str)
	{
		if (!quote && ft_strchr("\'\"", *str))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else if (*str == '$' && *(str + 1)
			&& !ft_strchr(" $", *(str + 1)) && quote != '\'')
		{
			env_len = get_envlen_and_find(str, &envar, env, quote);
			if (envar)
				tot_len += envar->word_len;
			str += env_len;
		}
		else
			tot_len++;
		str++;
	}
	return (tot_len);
}

static void	ft_memcpy_env(void *dst, const void *src, size_t n, int *i)
{
	ft_memcpy(dst, src, n);
	*i += n;
}

static void	update_with_env(char *str, t_list **env, int tot_len, char *ptr)
{
	int			i;
	int			env_len;
	t_envar		*envar;
	static char	quote = 0;

	i = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else if (*str == '$' && *(str + 1)
			&& !ft_strchr(" $", *(str + 1)) && quote != '\'')
		{
			env_len = get_envlen_and_find(str, &envar, env, quote);
			if (envar)
				ft_memcpy_env(&ptr[i], envar->word, envar->word_len, &i);
			str += env_len;
		}
		else
			ptr[i++] = *str;
		str++;
	}
	ptr[tot_len] = '\0';
}

int	find_tilde(char *str, t_list **env, char **home_ptr)
{
	t_list	*found;
	t_envar	*envar;

	if (*str != '~' || !ft_strchr("/\0", *(str + 1)))
		return (0);
	found = found_env(env, NULL, "HOME", 5);
	if (!found)
		return (0);
	envar = (t_envar *)(found->content);
	*home_ptr = envar->word;
	return (envar->word_len);
}

char	*check_update_env(char *str, t_list **env)
{
	int		home_len;
	char	*home_ptr;
	int		tot_len;
	char	*ptr;

	home_len = find_tilde(str, env, &home_ptr);
	if (home_len > 0)
		str++;
	tot_len = return_env_len(str, env) + home_len;
	ptr = malloc(sizeof(char) * (tot_len + 1));
	if (home_len > 0)
		ft_memcpy(ptr, home_ptr, home_len);
	update_with_env(str, env, tot_len, &(ptr[home_len]));
	return (ptr);
}
