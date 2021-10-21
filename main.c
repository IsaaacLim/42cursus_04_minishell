#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

#include <unistd.h>
#include <limits.h>

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

void	ft_getpath()
{
	//https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current working dir: %s\n", cwd);
	else
		perror("getcwd() error");	
}

void	ft_changepath()
{
	//https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
	chdir("..");
}

int	main()
{
	// ft_readline();
	ft_getpath();
	ft_changepath();
	ft_getpath();
}