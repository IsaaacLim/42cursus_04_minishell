#include "minishell.h"

/*
** Used as error handling for libft functions
** perror / strerror will be used for built-in library functions
*/
void	ft_error(char *message)
{
	printf("%s\n", message);
	exit (0);
}

/*
** Used as error handling for library functions
** Prints error message then exit program
*/
void	ft_perror(char *message)
{
	perror(message);
	exit (1);
}
