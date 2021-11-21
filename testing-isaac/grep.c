#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//to test pipe
int	main(int argc, char * argv[])
{
	execve("/usr/bin/grep", argv, NULL);
	printf("grep called but didn't execute\n");	
}
