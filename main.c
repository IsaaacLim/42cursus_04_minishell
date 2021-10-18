#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	ft_sigint()
{
	printf("Cya\n");
	exit (0);
}

void	ft_sigquit()
{
	printf("Bye\n");
	exit (0);
}

void	ft_readline()
{
	char	*inpt;

	while (1)
	{
		inpt = readline("Enter text: ");
		if(strlen(inpt) > 0)
			add_history(inpt);
		if (!strcmp(inpt, "exit"))
			exit(0);
		else if(!strcmp(inpt, "ls"))
			system("ls");
		free(inpt);
	}
}

int	main()
{
	signal(SIGINT, ft_sigint);	//ctrl - C
	signal(SIGQUIT, ft_sigquit); //ctrl - \ /
	ft_readline();
}
