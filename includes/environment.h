/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:58:07 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/30 17:58:07 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_envar
{
	char	*name;
	bool	set;
	char	*word;
	int		word_len;
}				t_envar;

// Environment utilities (e.g. intiialisation)
t_envar	*parse_env_var(char *env_str);
t_list	*initialise_env(char **envp);
void	free_envar(void *content);
void	print_env(t_list *env);
t_list	*found_env(t_list **env, t_list **prev, char *env_str, int search_len);

// Check for valid identifier
bool	valid_identifier(char *str);
void	invalid_identifier_msg(char *cmd, char *name);

// Commands
int		unset(t_list **env, char *env_str);
int		export_add(t_list **env, char *env_str);

// main function call
int		ft_environment(char *argv[], t_list *env);

#endif
