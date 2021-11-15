#include "minishell.h"

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
			return;
		}
		else if (ft_strlen(cmd_input) > 0)
		{
			add_history(cmd_input);
		}
		free(cmd_input);
	}
}
