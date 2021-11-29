#include "environment.h"

static void env_command(t_list *env)
{
	t_envar *envar;

	while (env)
	{
		envar = (t_envar *)env->content;
		if (envar->set)
			printf("%s=%s\n", envar->name, envar->word);
		env = env->next;
	}
}

int	ft_display_env(t_list *env, char **args)
{
	if (args[1])
	{
		printf("only env with no options or arguments\n");
		return (127);
	}
	else
		env_command(env);
	return (0);
}
