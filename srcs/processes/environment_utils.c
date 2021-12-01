/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinlim <jinlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:18:16 by jkhong            #+#    #+#             */
/*   Updated: 2021/12/01 20:59:54 by jinlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "minishell.h"

/*
	Validation of env_str occurs prior to execution of function
	- refer env_validate.c
	Traverses through env_str and malloc name and word delimited by '='
	variables without '=' specified will marked false for set attribute
*/
t_envar	*parse_env_var(char *env_str)
{
	int		len;
	t_envar	*envar;

	envar = malloc(sizeof(t_envar));
	len = 0;
	while (env_str[len] != '=' && env_str[len] != '\0')
		len++;
	if (env_str[len] == '=')
		envar->set = true;
	else
		envar->set = false;
	envar->name = malloc(sizeof(char) * (len + 1));
	ft_memcpy(envar->name, env_str, len);
	(envar->name)[len] = '\0';
	env_str += len;
	if (envar->set)
		env_str++;
	len = ft_strlen(env_str);
	envar->word = malloc(sizeof(char) * (len + 1));
	ft_memcpy(envar->word, env_str, sizeof(char) * (len + 1));
	envar->word_len = len;
	return (envar);
}

/*
	Reads preliminary envp variable passed in via main function
	- to be executed once in main
	Also initialises error variable, ?, called via $? in terminal
	- error variable is allocated ?=000 as min/max error value is 0/255
	  which is equivalent to unsigned char type
	- global variable is set to point ?=000 and is NUL terminated to
	  appropriately output 0
*/
t_list	*initialise_env(char **envp)
{
	int		i;
	t_list	*env_ptr;

	i = 0;
	env_ptr = NULL;
	while (envp[i])
		ft_lstadd_back(&env_ptr, ft_lstnew(parse_env_var(envp[i++])));
	g_exstat.env = parse_env_var("?=000");
	(g_exstat.env->word)[1] = '\0';
	ft_lstadd_back(&env_ptr, ft_lstnew(g_exstat.env));
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
/*
	Performs 2 functionalities:
	i. find env variable of search_len
		- return ptr_add or NULL if not found
	ii. (optional) to pass in pointer to t_list *prev
		- pass in NULL to ignore
		- else *prev updated with previous list node address
		- primarily for use in unset.c
*/
t_list	*found_env(t_list **env, t_list **prev, char *env_str, int search_len)
{
	t_list	*tmp_lst;
	t_envar	*tmp_env;

	tmp_lst = *env;
	while (tmp_lst)
	{
		tmp_env = (t_envar *)tmp_lst->content;
		if (ft_strncmp(tmp_env->name, env_str, search_len) == 0)
			return (tmp_lst);
		if (prev)
			*prev = tmp_lst;
		tmp_lst = tmp_lst->next;
	}
	return (NULL);
}
