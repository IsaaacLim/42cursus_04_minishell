#include "minishell.h"

/*
** Used to pass into libft's ft_lstclear.c
*/
void	ft_lstdel(void *content)
{
	ft_bzero(content, ft_strlen(content));
	free(content);
}

/*
** Prints all content stored in the List
** Will modify this for "echo"
*/
void	ft_putlst(t_list *lst) //temporary
{
	while (lst)
	{
		printf("%s ", (char *)lst->content);
		lst = lst->next;
	}
	printf("\n");
}
