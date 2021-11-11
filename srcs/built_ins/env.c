#include "environment.h"

void env_command(t_list *env)
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
