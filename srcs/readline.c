#include "minishell.h"

void	ft_free_double_arr(char **arr)
{
	int i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		i++;
	while (--i >= 0)
	{
		ft_bzero(arr[i], ft_strlen(arr[i]));
		free(arr[i]);
	}
	free(arr);
	return ;
}

void	ft_init_struct(t_input *input)
{
	input->has_greater_than = false;
	input->has_less_than = false;
	input->has_append = false;
}

void	ft_reset(t_input *input)
{
	ft_free_double_arr(input->double_arr);
	input->has_greater_than = false;
	input->has_less_than = false;
	input->has_append = false;
}

void	ft_parse(t_input *input)
{
	if (input->double_arr[0][0] == '>')
		input->has_greater_than = true;
	if (!(ft_strncmp(input->double_arr[0], "echo", 5)))
		printf("Call echo\n");
}

/*
** ------ COMBINED WITH INT MAIN ------
** Run infinitely unless "exit" or force termninated
** Input are stored into a linked list to be parsed to other functions
*** TO DO:
*** Change command prompt
*** Clear list before new inputs (& only after first input)
*** Check for memory leaks upon "exit" 
*/
// void	ft_readline(t_subprocess *p)
// {
// 	char	*input_arr;
// 	t_input	input;

// 	// ft_init_struct(&input);
// 	while (1)
// 	{
// 		input_arr = readline("Enter text: ");
// 		if (!ft_strncmp(input_arr, "exit", 5))
// 		{
// 			free(input_arr);
// 			// rl_clear_history(); //implicit declaration of function
// 			return;
// 		}
// 		else if (ft_strlen(input_arr) > 0)
// 		{
// 			add_history(input_arr);
// 			// input.double_arr = ft_split(input_arr, ' ');
// 			// ft_parse(&input); //mod with JR
// 			// ft_fork(input.double_arr, p);
// 			// ft_reset(&input);
// 			read_str(input_arr);
// 			free(input_arr);
// 		}
// 	}
// }
