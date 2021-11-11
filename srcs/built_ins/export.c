#include "environment.h"

int ft_lstlen(t_list *lst)
{
	int len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

// do i even need to do this?
void sort_print(t_envar ***env, int len)
{
	int i;
	int j;
	t_envar **ptr;
	t_envar *tmp;

	ptr = *env;
	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(ptr[i]->name, ptr[j]->name, __INT_MAX__) > 0)
			{
				tmp = ptr[i];
				ptr[i] = ptr[j];
				ptr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void export_command(t_list *env)
{
	int len;
	t_envar **tmp_arr;
	int i;

	len = ft_lstlen(env);
	tmp_arr = malloc(sizeof(t_envar *) * len);
	i = 0;
	while (env)
	{
		tmp_arr[i++] = (env)->content;
		env = env->next;
	}
	// SORT
	sort_print(&tmp_arr, len);
	// PRINT
	i = 0;
	// to exclude environment variable _
	while (i < len - 1)
	{
		printf("%s", tmp_arr[i]->name);
		if (tmp_arr[i]->set)
			printf("=\"%s\"", tmp_arr[i]->word);
		printf("\n");
		i++;
	}
	free(tmp_arr);
}

int error = false;


void export_add(t_list **env, char *env_str)
{
	t_envar *parse_env;
	t_list *found;
	// code validation function to check string for both environment name and word
	parse_env = parse_env_var(env_str);
	if (error)
	{
		free_envar((void *)parse_env);
		return;
	}
	found = found_env(env, NULL, parse_env->name);
	if (!found)
		ft_lstadd_back(env, ft_lstnew((void *)parse_env));
	else
	{
		free_envar(found->content);
		found->content = parse_env;
		return;
	}
}


// int main(int argc, char *argv[], char *envp[])
// {
// 	t_list *env;

// 	env = initialise_env(envp);

// 	unset(&env, "XDG_DATA_DIRS");
// 	unset(&env, "WSL_INTEROP");
// 	unset(&env, "WSL_DISTRO_NAME");
// 	// export_add(&env, "WSL_DISTRO_NAME=lsajfd");
// 	// env(env);
// 	export_command(env);

// 	// to free -> include towards end of main
// 	ft_lstclear(&env, free_envar);
// 	return (0);
// }

/* considerations
	- capture open and close quotes, even if user didnt add them
	- e.g. export what=asd asd -> what="asd"
		- export display will show open and close quotes
	- trim export input via parsing?

*/
// int main(void)
// {
// 	t_envar *envar = parse_env_var("TERM_PROGRAM=vscode");

// 	printf("%s, %i, %s\n", envar->name, envar->set, envar->word);
// 	return (0);
// }
