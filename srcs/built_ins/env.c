#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	int	i;

	if (argc != 1)
	{
		printf("env: execute without options or arguments\n");
		return (127);
	}
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (0);
}
