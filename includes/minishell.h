#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_subprocess
{
	pid_t pid;
	int stdin;
	int stdout;
} t_subprocess;

//error.c
void ft_error(char *message);

//fork.c
void ft_fork(char *argv[], t_subprocess *p);

//lst_utils.c
void ft_lstdel(void *content);
void ft_putlst(t_list *lst);

//readline.c
void ft_readline();

#endif
