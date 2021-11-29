#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int	main(int argc, char *argv[])
{
	char cwd[PATH_MAX];

	if (argc != 1)
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	else if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd lib function failed to execute");
		return (2);
	}
}
