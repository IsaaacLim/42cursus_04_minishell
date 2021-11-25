#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//to test pipe
int	main(int argc, char * argv[])
{
	execve("/usr/bin/wc", argv, NULL);
	printf("wc called but didn't execute\n");	
}
