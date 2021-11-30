/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:50:11 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 13:50:11 by jkhong           ###   ########.fr       */
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
		else if (*str == '$' && *(str + 1) &&
			!ft_strchr(" $", *(str + 1)) && quote != '\'')
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

static void	*update_with_env(char *str, t_list **env, int tot_len, char *ptr)
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

char	*check_update_env(char *str, t_list **env)
{
	int		tot_len;
	char	*ptr;

	tot_len = return_env_len(str, env);
	ptr = malloc(sizeof(char) * (tot_len + 1));
	update_with_env(str, env, tot_len, ptr);
	return (ptr);
}
