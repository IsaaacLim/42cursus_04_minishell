/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:18:16 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 15:18:16 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_envar	*parse_env_var(char *env_str)
{
	int		len;
	t_envar	*envar;

	envar = malloc(sizeof(t_envar));
	len = 0;
	env_str = env_str;
	while (env_str[len] != '=' && env_str[len] != '\0')
		len++;
	if (env_str[len] == '=')
		envar->set = true;
	else
		envar->set = false;
	envar->name = malloc(sizeof(char) * (len + 1));
	// update name
	ft_memcpy(envar->name, env_str, len);
	(envar->name)[len] = '\0';
	if (!envar->set)
		return (envar);
	// move position to after equals, =
	env_str = env_str + len + 1;
	len = ft_strlen(env_str);
	envar->word = malloc(sizeof(char) * (len + 1));
	ft_memcpy(envar->word, env_str, sizeof(char) * (len + 1));
	envar->word_len = len;
	return (envar);
}

/*
	Basically copies envp to env list format
*/
t_list	*initialise_env(char **envp)
{
	int		i;
	t_list	*env_ptr;

	i = 0;
	env_ptr = NULL;
	while (envp[i])
		ft_lstadd_back(&env_ptr, ft_lstnew(parse_env_var(envp[i++])));
	return (env_ptr);
}

void	free_envar(void *content)
{
	t_envar	*envar;

	envar = (t_envar *)content;
	if (!envar)
		return ;
	if (envar->name)
		free(envar->name);
	if (envar->word)
		free(envar->word);
	free(content);
}

void	print_env(t_list *env)
{
	t_envar	*envar;

	while (env)
	{
		envar = (t_envar *)env->content;
		printf("%s", envar->name);
		if (envar->set)
			printf("=\"%s\"\n", envar->word);
		env = env->next;
	}
}

// Accepts NULL as *prev in case we don't need our prev t_list
t_list	*found_env(t_list **env, t_list **prev, char *env_str, int search_len)
{
	t_list	*tmp_lst;
	t_envar	*tmp_env;

	tmp_lst = *env;
	while (tmp_lst)
	{
		// need to typecast that's why pretty confusing
		tmp_env = (t_envar *)tmp_lst->content;
		if (ft_strncmp(tmp_env->name, env_str, search_len) == 0)
			return (tmp_lst);
		if (prev)
			*prev = tmp_lst;
		tmp_lst = tmp_lst->next;
	}
	return (NULL);
}
