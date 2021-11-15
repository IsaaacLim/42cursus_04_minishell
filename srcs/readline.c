#include "minishell.h"

void	ft_free_double_arr(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		i++;
	printf("free: %d\n", i);
	while (--i >= 0)
	{
		ft_bzero(arr[i], ft_strlen(arr[i]));
		free(arr[i]);
	}
	free(arr);
	return ;
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
	char	*input_arr;
	char	**split_arr; //might want to put this in a struct

	while (1)
	{
		input_arr = readline("Enter text: ");
		if (!ft_strncmp(input_arr, "exit", 5))
		{
			free(input_arr);
			// rl_clear_history(); //implicit declaration of function
			return;
		}
		else if (ft_strlen(input_arr) > 0)
		{
			add_history(input_arr);
			split_arr = ft_split(input_arr, ' ');
			//ft_parse(t_struct)
			ft_free_double_arr(split_arr);
		}
		free(input_arr);
	}
}
