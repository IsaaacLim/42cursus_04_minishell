#include "environment.h"

// replace this with validation checks
static int error = false;

void unset(t_list **env, char *env_str)
{
	t_envar *parse_env;
	t_list *found;
	t_list *prev;

	prev = NULL;
	parse_env = parse_env_var(env_str);
	if (error)
		;
	else
	{
		found = found_env(env, &prev, parse_env->name, INT_MAX);
		if (found)
		{
			prev->next = found->next;
			ft_lstdelone(found, free_envar);
		}
	}
	free_envar(parse_env);
}