/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:17:41 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 18:17:41 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
	Purpose:
	Sorts environment variable by NAME in alphabetical order
*/
static void	sort_env(t_envar ***env, int len)
{
	int		i;
	int		j;
	t_envar	**ptr;
	t_envar	*tmp;

	ptr = *env;
	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(ptr[i]->name, ptr[j]->name, INT_MAX) > 0)
			{
				tmp = ptr[i];
				ptr[i] = ptr[j];
				ptr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

/*
	Constructs temporary array tmp_arr to order
	environment variables alphabetically using sort_env
*/
void	export_command(t_list *env)
{
	int		len;
	t_envar	**tmp_arr;
	int		i;

	len = ft_lstsize(env);
	tmp_arr = malloc(sizeof(t_envar *) * len);
	i = 0;
	while (env)
	{
		tmp_arr[i++] = (env)->content;
		env = env->next;
	}
	sort_env(&tmp_arr, len);
	i = 0;
	while (i < len)
	{
		printf("%s", tmp_arr[i]->name);
		if (tmp_arr[i]->set)
			printf("=\"%s\"", tmp_arr[i]->word);
		printf("\n");
		i++;
	}
	free(tmp_arr);
}

int error = false;

/*
	Adds additional variable into env struct
*/
void	export_add(t_list **env, char *env_str)
{
	t_envar		*parse_env;
	t_list		*found;

	parse_env = parse_env_var(env_str);
	// if (!valid_identifier(parse_env->name))
	if (error)
	{
		invalid_identifier_msg("export", parse_env->name);
		free_envar((void *)parse_env);
		return ;
	}
	printf("%s\n", parse_env->name);
	printf("%s\n", parse_env->word);
	found = found_env(env, NULL, parse_env->name, INT_MAX);
	if (!found)
		ft_lstadd_back(env, ft_lstnew((void *)parse_env));
	else
	{
		free_envar(found->content);
		found->content = parse_env;
		return ;
	}
}
