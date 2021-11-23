# ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

typedef struct s_envar
{
	char *name;
	bool set;
	char *word;
}           t_envar;

// Environment utilities (e.g. intiialisation)
t_envar	*parse_env_var(char *env_str);
t_list *initialise_env(char **envp);
void free_envar(void *content);
void print_env(t_list *env);
t_list *found_env(t_list **env, t_list **prev, char *env_str);

// Commands
void env_command(t_list *env);
void unset(t_list **env, char *env_str);
void export_command(t_list *env);
void export_add(t_list **env, char *env_str);

// main function call
int ft_environment(char *argv[]);

#endif
