#include "minishell.h"
#include "libft.h"

void	ft_error(char *message)
{
	printf("%s", message);
	exit (0);
}

void	ft_putlist(t_list *list)
{
	while (list)
	{
		printf("%s ", (char *)list->content);
		list = list->next;
	}
	printf("\n");
}

static void	ft_clearArray(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		ft_bzero(arr[i], ft_strlen(arr[i]));
		free(arr[i]);
	}
	free(arr);
}

static void	ft_createList(t_list **input_list, char *cmd_input)
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
		ft_lstadd_back(input_list, new);
	}
	// printf("%s\n", (char *)(*input_list)->content);
	// ft_clearArray(temp_arr);
}

void	ft_readline()
{
	char	*cmd_input;
	t_list	*input_list;

	while (1)
	{
		cmd_input = readline("Enter text: ");
		if (!ft_strncmp(cmd_input, "exit", 4))
			exit (0); //check for leaks if exit
		else if (ft_strlen(cmd_input) > 0)
		{
			add_history(cmd_input);
			ft_createList(&input_list, cmd_input);
		}
		free(cmd_input);
		// printf("%s\n", (char *)input_list->content);
		ft_putlist(input_list);
	}
}
