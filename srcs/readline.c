#include "minishell.h"
#include "libft.h"

void	ft_readline()
{
	char	*input;

	while (1)
	{
		input = readline("Enter text: ");
		if (ft_strlen(input) > 0)
			add_history(input);
		if (!ft_strncmp(input, "exit", 4))
			exit (0);
		free(input);
	}
}
