#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>
#include <string.h>

#include "minishell.h"
#include "environment.h"
#include "libft.h"

// void ft_free_double_arr(char **arr)
// {
// 	int i;

// 	if (!arr)
// 		return;
// 	i = 0;
// 	while (arr[i])
// 		i++;
// 	while (--i >= 0)
// 	{
// 		ft_bzero(arr[i], ft_strlen(arr[i]));
// 		free(arr[i]);
// 	}
// 	free(arr);
// 	return;
// }

// This assumes that str and track would have the same length
bool valid_quotes(char *str, char *track, char to_rep, char rep_to)
{
	char *ptr;
	char quote;

	quote = 0;
	while (*str)
	{
		if (quote && *str == to_rep)
		{
			*track = 1;
			*str = rep_to;
		}
		else if (*str == quote)
		{
			if (*str == '\'')
				*track = '\'';
			else if (*str = '\"')
				*track = '\"';
			quote = 0;
		}
		else if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		str++;
		track++;
	}
	if (quote)
		return (false);
	return (true);
}

void replace_quotes(char *str, char rep_to)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			*str = rep_to;
		str++;
	}
}

/*
	Assumes that ft_split will mainly use ' ' spaces for delimiting and splitting

	removed rep_to
*/
void replace_char_quotes(char **str_arr, char *str, char *track, char rep_to)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			if (track[i] == 1)
				(*str_arr)[j] = rep_to;
			// need to increment whenever a != ' ' is found
			j++;
			if ((*str_arr)[j] == '\0')
			{
				str_arr++;
				j = 0;
			}
		}
		i++;
	}
}

/*
	Purpose: to indicate whether string is bounded by a single or double quote
*/
char *return_quote_type(char **str_arr, char *str, char *track)
{
	int len;
	char *tmp;
	int i;

	len = 0;
	tmp = NULL;
	// not iterate with str_arr[len][0]?
	while (str_arr[len])
		len++;
	tmp = ft_calloc(len, sizeof(char));
	i = 0;
	while (*str)
	{
		if (*str != ' ' && (*(str + 1) == ' ' || *(str + 1) == '\0') && str_arr[i])
		{
			// printf("%i\n", i);
			if (*(track + 1) == '\'')
				tmp[i] = '\'';
			else if (*(track + 1) == '\"')
				tmp[i] = '\"';
			i++;
		}
		str++;
		track++;
	}
	return (tmp);
}

/*
	returns NULL if failed, i.e.
	- invalid quotes
*/
char **ft_split_enhanced(char *str, char c)
{
	char **str_arr;
	char *track;

	track = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	str_arr = NULL;
	if (valid_quotes(str, track, c, -1))
	{
		str_arr = ft_split(str, c);
		replace_char_quotes(str_arr, str, track, c);
	}
	free(track);
	return (str_arr);
}

t_envar *found_null_term_env(t_list **env, char *ptr, int env_len)
{
	t_list *found;
	t_envar *envar;
	char c;

	// replaces ptr[env_len] temporarily to null terminate
	c = ptr[env_len];
	ptr[env_len] = '\0';
	found = found_env(env, NULL, ptr, INT_MAX);
	ptr[env_len] = c;
	if (found)
		return ((t_envar *)(found->content));
	return (NULL);
}

/*
	Empty $ returns nothing
	Edge cases
	- checked for replacement 

	Add condition to confirm that no environment variables noted

	Returns -1 if no changes are required to be made
*/
int return_env_len2(char *str, t_list **env)
{
	int tot_len;
	int env_len;
	char *ptr;
	t_envar *envar;
	bool to_update;

	tot_len = 0;
	to_update = false;
	while (*str)
	{
		if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '$' && *(str + 1))
		{
			// need this to return whether to malloc a new string or not
			to_update = true;
			ptr = str + 1;
			env_len = 0;
			// check to make sure that side by side $ works as well...
			while (ptr[env_len] && ptr[env_len] != ' ' && ptr[env_len] != '$')
				env_len++;
			envar = found_null_term_env(env, ptr, env_len);
			if (envar)
				tot_len += envar->word_len;
			str += env_len;
		}
		else
			tot_len++;
		str++;
	}
	if (!to_update)
		return (-1);
	return (tot_len);
}

/*
	Process env variables
	-> pass in t_cmd
	-> splits out t_cmd with updated string
*/
char *update_with_env2(char *str, t_list **env, int tot_len)
{
	char *tmp;
	int i;
	int env_len;
	char *ptr;
	t_envar *envar;

	tmp = malloc(sizeof(char) * (tot_len + 1));
	i = 0;
	while (*str)
	{
		if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '$' && *(str + 1))
		{
			ptr = str + 1;
			env_len = 0;
			while (ptr[env_len] && ptr[env_len] != ' ' && ptr[env_len] != '$')
				env_len++;
			envar = found_null_term_env(env, ptr, env_len);
			if (envar)
			{
				ft_memcpy(&tmp[i], envar->word, envar->word_len);
				i += envar->word_len;
			}
			str += env_len;
		}
		else
			tmp[i++] = *str;
		str++;
	}
	tmp[tot_len] = '\0';
	return (tmp);
}

char *check_update_env2(char *str, t_list **env)
{
	int len;

	len = return_env_len2(str, env);
	if (len != -1)
		return (update_with_env2(str, env, len));
	return (ft_strcpy(str));
}

int return_env_len(char *str, t_list **env)
{
	int tot_len;
	int env_len;
	char *ptr;
	t_envar *envar;
	bool to_update;
	char quote;

	quote = 0;
	tot_len = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '$' && quote != '\'' && *(str + 1))
		{
			// need this to return whether to malloc a new string or not
			ptr = str + 1;
			env_len = 0;
			// check to make sure that side by side $ works as well...
			while (ptr[env_len] && ptr[env_len] != ' ' && ptr[env_len] != '$' && ptr[env_len] != quote && ptr[env_len])
				env_len++;
			envar = found_null_term_env(env, ptr, env_len);
			if (envar)
				tot_len += envar->word_len;
			str += (env_len - 1);
		}
		else
			tot_len++;
		str++;
	}
	return (tot_len);
}

char *update_with_env(char *str, t_list **env, int tot_len)
{
	char *tmp;
	int i;
	int env_len;
	char *ptr;
	t_envar *envar;
	char quote;

	quote = 0;
	tmp = malloc(sizeof(char) * (tot_len + 1));
	i = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '\"'))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '$' && quote != '\'' && *(str + 1))
		{
			ptr = str + 1;
			env_len = 0;
			while (ptr[env_len] && ptr[env_len] != ' ' && ptr[env_len] != '$' && ptr[env_len] != quote && ptr[env_len])
				env_len++;
			envar = found_null_term_env(env, ptr, env_len);
			if (envar)
			{
				ft_memcpy(&tmp[i], envar->word, envar->word_len);
				i += envar->word_len;
			}
			str += env_len;
		}
		else
			tmp[i++] = *str;
		str++;
	}
	tmp[tot_len] = '\0';
	return (tmp);
}

char *check_update_env(char *str, t_list **env)
{
	int len;

	len = return_env_len(str, env);
	return (update_with_env(str, env, len));
}

int main5(int argc, char *argv[], char *envp[])
{
	t_list *env = initialise_env(envp);

	char str[] = "\"$WSL_DISTRO_NAME\"'$WSL_DISTRO_NAME' ";
	char *tmp;

	int len;

	len = return_env_len2(str, &env);
	if (len != -1)
		tmp = update_with_env2(str, &env, len);
	else
		tmp = ft_strcpy(str);
	printf("%i\n", len);
	printf("%s\n", tmp);
	free(tmp);
	ft_lstclear(&env, free_envar);
	return (0);
}

/*
	Performs 2 things
	1. Replaces char with
*/
void replace_char(char **str_arr, char *str, char *track, char rep_to)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (track[i])
			str[i] = rep_to;
		i++;
	}
}

int main2(void)
{
	char str[] = "\"echo\"";
	// need to calloc
	char *track = ft_calloc(ft_strlen(str), sizeof(char));

	if (valid_quotes(str, track, ' ', -1))
	{
		replace_char(NULL, str, track, ' ');
		replace_quotes(str, ' ');
		printf("%s\n", str);
	}
	// remember to free
	free(track);
	return (0);
}

int main3()
{
	char str[] = "\"export\"";
	char str2[] = "export";
	char **str_arr = ft_split_enhanced(str, ' ');
	char **str_arr2 = ft_split(str, ' ');

	printf("%i\n", ft_strncmp(str_arr[0], str_arr2[0], INT_MAX));
	if (str_arr2)
	{
		char **tmp = str_arr2;
		while (*tmp)
			printf("%s\n", *tmp++);
		ft_free_double_arr(str_arr2);
	}
	return (0);
}

int main4(int argc, char *argv[], char *envp[])
{
	t_list *env = initialise_env(envp);
	// print_env(env);
	// printf("\n\n");
	char str[] = "";
	char *tmp;

	tmp = check_update_env(str, &env);
	printf("%s\n", tmp);
	free(tmp);
	ft_lstclear(&env, free_envar);
	return (0);
}

// int main(int argc, char *argv[], char *envp[])
// {
// 	main5(argc, argv, envp);
// }