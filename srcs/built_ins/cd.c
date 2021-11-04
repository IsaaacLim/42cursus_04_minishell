#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	(void)argc;

	chdir(argv[1]);
}
