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
	Assumes that ft_split will mainly use ' ' spaces for delimiting and splitting

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
	returns NULL if failed, i.e.
	- invalid quotes
*/
char **ft_split_enhanced(char *str, char c)
{
    char **str_arr;
    char *track;

    track = ft_calloc(ft_strlen(str), sizeof(char));
    str_arr = NULL;
    if (valid_quotes(str, track, c, -1))
    {
        replace_quotes(str, c);
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
int return_env_len(char *str, t_list **env)
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
char *update_with_env(char *str, t_list **env, int tot_len)
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

char *check_update_env(char *str, t_list **env)
{
    int len;

    len = return_env_len(str, env);
    if (len != -1)
        return (update_with_env(str, env, len));
    return (ft_strcpy(str));
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
    // char str[] = "'hey' Hi \"  world\" ' asdf asdf   sadf sad f sda f sad f'";
    char str[] = "\"export\"";
    char str2[] = "export";
    char **str_arr = ft_split_enhanced(str, ' ');
    char **str_arr2 = ft_split(str, ' ');

    printf("%i\n", ft_strncmp(str_arr[0], str_arr2[0], INT_MAX));
    // int i = 0;
    // while (str_arr[0][i] && str_arr2[0][i])
    // {
    // 	printf("%i %i %c %c\n", str_arr[0][i], str_arr[0][i], str_arr2[0][i], str_arr2[0][i]);
    // 	i++;
    // }
    // printf("%i %i %c %c\n", str_arr[0][i], str_arr[0][i], str_arr2[0][i], str_arr2[0][i]);
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
// 	main3(argc, argv, envp);
// }