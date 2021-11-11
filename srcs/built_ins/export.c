#include "../../libft/includes/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

/*
	TO handle?
		- errors? edge cases?
*/

typedef struct s_envar
{
	char *name;
	bool set;
	char *word;
} t_envar;

t_envar *parse_env_var(char *env_str)
{
	int len;
	t_envar *envar;

	envar = malloc(sizeof(t_envar));
	len = 0;
	env_str = env_str;
	while (env_str[len] != '=' && env_str[len] != '\0')
		len++;
	if (env_str[len] == '=')
		envar->set = true;
	else
		envar->set = false;
	envar->name = malloc(sizeof(char) * (len + 1));
	// update name
	ft_memcpy(envar->name, env_str, len);
	(envar->name)[len] = '\0';
	if (!envar->set)
		return (envar);
	// update word, + 1 to include null pointer
	env_str = env_str + len + 1;
	len = ft_strlen(env_str) + 1;
	envar->word = malloc(sizeof(char) * len);
	ft_memcpy(envar->word, env_str, sizeof(char) * len);
	return (envar);
}

/*
	Basically copies envp to env list format
*/
t_list *initialise_env(char **envp)
{
	int i;
	t_list *env_ptr;

	i = 0;
	env_ptr = NULL;
	while (envp[i])
	{
		ft_lstadd_back(&env_ptr, ft_lstnew(parse_env_var(envp[i])));
		i++;
	}
	return (env_ptr);
}

void free_envar(void *content)
{
	t_envar *envar;

	envar = (t_envar *)content;
	free(envar->name);
	free(envar->word);
	free(content);
}

void print_env(t_list *env)
{
	t_envar *envar;

	while (env)
	{
		envar = (t_envar *)env->content;
		printf("%s", envar->name);
		if (envar->set)
		{
			printf("=\"%s\"\n", envar->word);
		}
		env = env->next;
	}
}

bool is_subset(char c, char *subset)
{
	while (*subset)
	{
		if (c == *subset)
			return (true);
		subset++;
	}
	return (false);
}

bool valid_identifier(char *name)
{
	const char c = name[0];
	// https://user-web.icecube.wisc.edu/~dglo/c_class/charfunc.html#:~:text=In%20ASCII%2C%20whitespace%20characters%20are,formfeed%20(%20'%5Cf'%20).
	const char *whitespace = " \t\r\n\v\f";
	// https://www.oreilly.com/library/view/learning-the-bash/1565923472/ch01s09.html
	const char *spcial = "~`#$&*()\\|[]{};,<>/?!";

	if (!(c >= 'a' && c <= 'z') || !(c >= 'A' && c <= 'Z') || c != '_')
		return (false);
	name++;
	while (name)
	{
		if (!(c >= 'a' && c <= 'z') || !(c >= 'A' && c <= 'Z') || c != '_' || (c >= '0' && c <= '9'))
			return (false);
	}
	return (true);
}

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
		printf("declare -x %s", tmp_arr[i]->name);
		if (tmp_arr[i]->set)
			printf("=\"%s\"", tmp_arr[i]->word);
		printf("\n");
		i++;
	}
	free(tmp_arr);
}

int error = false;

t_list *found_env(t_list **env, t_list **prev, char *env_str)
{
	t_list *tmp_lst;
	t_envar *tmp_env;

	tmp_lst = *env;
	while (tmp_lst)
	{
		// need to typecast that's why pretty confusing
		tmp_env = (t_envar *)tmp_lst->content;
		if (ft_strncmp(tmp_env->name, env_str, __INT_MAX__) == 0)
			return (tmp_lst);
		if (prev)
			*prev = tmp_lst;
		tmp_lst = tmp_lst->next;
	}
	return (NULL);
}

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

void unset_command(t_list **env, char *env_str)
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
		found = found_env(env, &prev, parse_env->name);
		if (found)
		{
			prev->next = found->next;
			ft_lstdelone(found, free_envar);
		}
	}
	free_envar(parse_env);
}

int main(int argc, char *argv[], char *envp[])
{
	t_list *env;

	env = initialise_env(envp);

	unset_command(&env, "XDG_DATA_DIRS");
	unset_command(&env, "WSL_INTEROP");
	unset_command(&env, "WSL_DISTRO_NAME");
	// export_add(&env, "WSL_DISTRO_NAME=lsajfd");
	// env_command(env);
	export_command(env);

	// to free -> include towards end of main
	ft_lstclear(&env, free_envar);
	return (0);
}

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
