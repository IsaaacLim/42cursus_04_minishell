#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

//error.c
void	ft_error(char *message);

//lst_utils.c
void	ft_lstdel(void *content);
void	ft_putlst(t_list *lst);

//readline.c
void	ft_readline();

#endif
