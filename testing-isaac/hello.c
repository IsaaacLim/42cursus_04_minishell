#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    int i;

    printf("File name: %s\n", argv[0]);
    i = 0;
    while (++i < 5)
       printf("%s ", argv[i]);
    printf("\n");
}
