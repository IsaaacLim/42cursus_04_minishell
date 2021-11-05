#include "../../libft/includes/libft.h"
#include <stdio.h>
#include <stdbool.h>

/*
	TO handle?
		- errors? edge cases?
*/

/*
	Basically copies envp to env list format
*/
t_list *initialise_env(char **envp)
{
	int i;
	char *env_str;
	int env_len;
	t_list *env_ptr;

	i = 0;
	env_ptr = NULL;
	while (envp[i])
	{
		// mallocs line and copies to tmp char * variable, + 1 to include null pointer
		env_len = ft_strlen(envp[i]) + 1;
		env_str = malloc(sizeof(char) * env_len);
		ft_memcpy(env_str, envp[i], sizeof(char) * env_len);
		// append to end of list
		ft_lstadd_back(&env_ptr, ft_lstnew(env_str));
		i++;
	}
	return (env_ptr);
}

void print_env(t_list *env)
{
	while (env)
	{
		printf("%s\n", (char *)(env->content));
		env = env->next;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_list *env;

	env = initialise_env(envp);
	print_env(env);

	// to free -> include towards end of main
	ft_lstclear(&env, free);
	return (0);
}