/*
** Input are stored into a linked list to be parsed to other functions
** Don't forget to free with ft_lstclear
*/
static void ft_createList(t_list **input_lst, char *cmd_input)
{
	t_list *new;
	char **temp_arr;
	int i;

	temp_arr = ft_split(cmd_input, ' ');
	if (!temp_arr)
		ft_error("readline.c ft_createList ft_split error\n");
	i = -1;
	while (temp_arr[++i])
	{
		new = ft_lstnew(temp_arr[i]);
		ft_lstadd_back(input_lst, new);
	}
}

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
