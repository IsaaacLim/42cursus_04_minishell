#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char *test;

	test = malloc(-1);
	if (test == NULL)
	{
		perror("malloc failed");
		exit (8);
	}
	return (5);
}
