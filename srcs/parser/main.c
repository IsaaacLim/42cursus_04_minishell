#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void ft_readline()
{
	char *inpt;

	while (1)
	{
		inpt = readline("Enter text: ");
		if (strlen(inpt) > 0)
			add_history(inpt);
		if (!strcmp(inpt, "exit"))
			exit(0);
		else if (!strcmp(inpt, "ls"))
			system("ls");
		printf("%s\n", inpt);
		free(inpt);
	}
}

int main(void)
{
	ft_readline();
	return (2);
}