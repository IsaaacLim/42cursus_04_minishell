#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

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

void	ft_tty()
{
	int	i;
	int	t;

	i = 0;
	while (i < 100)
	{
		t = isatty(i);
		printf("%d ", t);
		i++;
	}
	printf("\n");
	printf("ttyname(0): %s\n", ttyname(0));
	printf("ttyname(1): %s\n", ttyname(1));
	printf("ttyname(2): %s\n", ttyname(2));
	printf("ttyname(3): %s\n", ttyname(3));
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
	ft_tty();
	ft_readline();
}
