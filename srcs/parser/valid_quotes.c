#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>
#include <string.h>

#include "minishell.h"
#include "environment.h"

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
			*str = ' ';
		str++;
	}
}

/*
	Performs 2 things
	1. Replaces char with
*/
void replace_char(char *str, char *track, char rep_to)
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
	Empty $ returns nothing
	Edge cases
	- checked for replacement 

	Add condition to confirm that no environment variables noted
*/
int	check_env(char *str, t_list **env)
{
	int tot_len;
	int env_len;
	char *ptr;
	t_list *found;
	t_envar *envar;
	char c;

	tot_len = 0;
	while (*str)
	{
		if (*str == '$' && *(str + 1) != ' ' && *(str + 1))
		{
			// printf("Why not working here %c\n", str[i]);
			ptr = str + 1;
			env_len = 0;
			// check to make sure that side by side $ works as well...
			while (ptr[env_len] && ptr[env_len] != ' ' && ptr[env_len] != '$')
				env_len++;
			c = ptr[env_len];
			ptr[env_len] = '\0';
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
		if (*str == '$' && *(str + 1) != ' ' && *(str + 1))
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

int main2(int argc, char *argv[])
{
	char str[] = "\"echo\"\'";
	// need to calloc
	char *track = calloc(strlen(str), sizeof(char));

	if (valid_quotes(str, track, ' ', -1))
	{
		replace_char(str, track, ' ');
		printf("%s\n", str);
	}
	// remember to free
	free(track);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_list *env = initialise_env(envp);
	// print_env(env);
	// printf("\n\n");
	char str[] = "HI $HELLO $PATH";

	printf("%i\n", check_env(str, &env));
	printf("%s\n", update_env(str, &env, check_env(str, &env)));
	return (0);
}
