#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    int i;

    // printf("File name: %s\n", argv[0]);
    // i = 0;
    // while (++i < 5)
    //    printf("%s ", argv[i]);
    int x = 0;
    while (envp[x])
    {
        printf("%s\n", envp[x]);
        x++;
    }
    // printf("\n");
}
