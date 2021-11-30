#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include <stdlib.h>
int	main(int argc, char *argv[])
{
	char cwd[PATH_MAX];


	char *env;
	env = getenv("PWD");
	if (!env)
		printf("No match\n");
	else
		printf("%s => %s\n", "PWD", env);

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
