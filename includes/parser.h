/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:16:31 by jkhong            #+#    #+#             */
/*   Updated: 2021/11/29 23:21:55 by jkhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "environment.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>

typedef enum e_redirection
{
	none,
	in,
	in_heredoc,
	out,
	out_append
}			t_redirection;

// Struct for simple command
typedef struct s_cmd
{
	char	**args;
	int		input;
	int		output;
	char	*infile;
	char	*outfile;
}				t_cmd;

// Struct to store array of simple commands
// and length of array
typedef struct s_commands
{
	t_cmd	*commands;
	int		len;
	char	*quote_type;
}			t_commands;

// Utility functions to be used in parser
int			num_pipes(char **str_arr);
int			is_redirection(char *str, t_cmd *cmd, char *next);
bool		valid_redirection(char **str_arr);
bool		valid_pipe(char **str_arr);
void		initialise_singlecmd(t_cmd *cmd);
t_commands	*initialise_t_commands(char **str_arr);
void		free_commands(t_commands *commands);

// Parser env utils
int			get_envlen_and_find(char *str,
				t_envar **envar, t_list **env, char quote);

// To update str with environment variable
char		*check_update_env(char *str, t_list **env);

// Enhanced ft_split to consider validity of quotes 
// and splitting according to quotes
char		**ft_split_enhanced(char *str, char c);

#endif