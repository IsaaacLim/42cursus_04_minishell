#include "minishell.h"

/*
** Used as error handling for libft functions
** perror / strerror will be used for built-in library functions
*/
void	ft_error(char *message)
{
	printf("%s", message);
	exit (0);
}
