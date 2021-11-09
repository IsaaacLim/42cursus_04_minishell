#include "minishell.h"

/*
** Input are stored into a linked list to be parsed to other functions
*/
static void	ft_createList(t_list **input_lst, char *cmd_input)
{
	t_list	*new;
	char	**temp_arr;
	int		i;

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
** Run infinitely unless "exit" or force termninated
** Input are stored into a linked list to be parsed to other functions
*** TO DO:
*** Change command prompt
*** Clear list before new inputs (& only after first input)
*** Check for memory leaks upon "exit" 
*/
void	ft_readline()
{
	char	*cmd_input;
	t_list	*input_lst;

	while (1)
	{
		cmd_input = readline("Enter text: ");
		if (!ft_strncmp(cmd_input, "exit", 5))
		{
			free(cmd_input);
			// rl_clear_history(); //implicit declaration of function
			return ;
		}
		else if (ft_strlen(cmd_input) > 0)
		{
			add_history(cmd_input);
			ft_createList(&input_lst, cmd_input);
			ft_putlst(input_lst); //temporary
			ft_lstclear(&input_lst, &ft_lstdel); //temporary
		}
		free(cmd_input);
	}
}
