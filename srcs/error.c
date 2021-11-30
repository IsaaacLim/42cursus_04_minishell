#include "minishell.h"

/*
** Used as error handling for libft functions
** perror / strerror will be used for built-in library functions
*/
void	ft_libft_error(char *strerror)
{
	printf("libft error: %s\n", strerror);
	exit (42);
}

/*
** Used as error handling for library functions
** Prints error message then exit program
*/
void	ft_perror(char *message)
{
	perror(message);
	exit (2);
}
