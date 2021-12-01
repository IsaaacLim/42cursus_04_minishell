#include "minishell.h"

/*
** Used as error handling for UNEXPECTING libft functions
** exit program if occurs
*/
void	ft_libft_error(char *strerror)
{
	printf("libft error: %s\n", strerror);
	exit (42);
}

/*
** Used as error handling for UNEXPECTING library functions
** exit program if occurs
*/
void	ft_perror_exit(char *message)
{
	perror(message);
	exit (24);
}
