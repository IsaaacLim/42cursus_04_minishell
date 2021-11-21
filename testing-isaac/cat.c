#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main (int argc, char *argv[])
{
	execve("/bin/cat", argv, NULL);
	printf("cat called but didn't execute");	
}
