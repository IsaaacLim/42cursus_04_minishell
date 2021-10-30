#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//https://tuxthink.blogspot.com/2012/06/using-execve.html?m=1
int main()
{
    char *temp[] = {NULL, "waddup", "world", "more", NULL};
    // temp[0] = "script.sh";
    // execve("script.sh", temp, NULL);
    temp[0] = "hello";
    execve("hello", temp, NULL);
    printf("It's not going to reach here\n");
}
