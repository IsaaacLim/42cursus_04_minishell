#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>
#include <string.h>

#include "minishell.h"
#include "environment.h"
#include "libft.h"

void ft_free_double_arr(char **arr)
{
	int i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
		i++;
	while (--i >= 0)
	{
		ft_bzero(arr[i], ft_strlen(arr[i]));
		free(arr[i]);
	}
	free(arr);
	return;
}

/*
	TO DO
	0 replace strlen and calloc with libft functions
*/

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
			quote = 0;
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

/*
	Assumes that ft_split will mainly use ' ' spaces for delimiting and splitting

*/
void replace_char2(char **str_arr, char *str, char *track, char rep_to)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		// printf("%i %c\n", str[i], str[i]);
		if (str[i] != ' ')
		{
			printf("%i %i\n", (*str_arr)[j], str[i]);
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
	Empty $ returns nothing
	Edge cases
	- checked for replacement 

	Add condition to confirm that no environment variables noted

	Returns -1 if no changes are required to be made
*/
int check_env(char *str, t_list **env)
{
	int tot_len;
	int env_len;
	char *ptr;
	t_list *found;
	bool to_update;
	t_envar *envar;
	char c;

	tot_len = 0;
	to_update = false;
	while (*str)
	{
		if (*str == '$' && *(str + 1) != ' ' && *(str + 1) != '$' && *(str + 1))
		{
			// printf("Why not working here %c\n", str[i]);
			ptr = str + 1;
			env_len = 0;
			// check to make sure that side by side $ works as well...
			while (ptr[env_len] && ptr[env_len] != ' ' && ptr[env_len] != '$')
				env_len++;
			c = ptr[env_len];
			ptr[env_len] = '\0';
			// need this to return whether to malloc a new string or not
			to_update = true;
			found = found_env(env, NULL, ptr, INT_MAX);
			if (found)
			{
				envar = (t_envar *)(found->content);
				if (envar->name[env_len] == '\0')
					tot_len += envar->word_len;
			}
			ptr[env_len] = c;
			str += env_len;
		}
		else
		{
			// printf("Hi %c\n", str[i]);
			tot_len++;
		}
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

char *update_env(char *str, t_list **env, int tot_len)
{
	char *tmp;
	int i;
	int env_len;
	char *ptr;
	t_list *found;
	t_envar *envar;
	char c;

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
			c = ptr[env_len];
			ptr[env_len] = '\0';
			found = found_env(env, NULL, ptr, INT_MAX);
			if (found)
			{
				envar = (t_envar *)(found->content);
				if (envar->name[env_len] == '\0')
				{
					ft_memcpy(&tmp[i], envar->word, envar->word_len);
					i += envar->word_len;
				}
			}
			ptr[env_len] = c;
			str += env_len;
		}
		else
			tmp[i++] = *str;
		str++;
	}
	tmp[tot_len] = '\0';
	return (tmp);
}

int main2(void)
{
	char str[] = "\"echo\"";
	// need to calloc
	char *track = calloc(strlen(str), sizeof(char));

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
	char str[] = "Hi \"  world\"";
	char **str_arr;
	// need to calloc
	char *track = calloc(strlen(str), sizeof(char));

	if (valid_quotes(str, track, ' ', -1))
	{
		replace_quotes(str, ' ');

		int i = 0;
		// while (str[i])
		// {
		// 	printf("%i\n", str[i++]);
		// }
		// ft_split
		str_arr = ft_split(str, ' ');

		replace_char2(str_arr, str, track, ' ');

		char **tmp = str_arr;
		while (*tmp)
			printf("%s\n", *tmp++);
		ft_free_double_arr(str_arr);
	}
	// remember to free
	free(track);
	return (0);
}

int main4(int argc, char *argv[], char *envp[])
{
	t_list *env = initialise_env(envp);
	// print_env(env);
	// printf("\n\n");
	char str[] = "HI $w$w OLDPWD";
	char *tmp;
	int len = check_env(str, &env);

	// Make sure clearing is done properly here
	if (len != -1)
		tmp = update_env(str, &env, check_env(str, &env));
	printf("%i\n", len);
	if (len != -1)
	{
		printf("%s\n", tmp);
		free(tmp);
	}
	else
		printf("%s\n", str);
	ft_lstclear(&env, free_envar);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	main3();
}