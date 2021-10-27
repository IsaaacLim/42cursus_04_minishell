#include "minishell.h"

void	ft_readline()
{
	char	*input;

	while (1)
	{
		input = readline("Enter text: ");
		if (strlen(input) > 0)
			add_history(input);
		if (!strcmp(input, "exit"))
			exit (0);
		free(input);
	}
}
