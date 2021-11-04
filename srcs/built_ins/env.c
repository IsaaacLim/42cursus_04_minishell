#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    int x;
    
    x = 0;
    while (envp[x])
    {
        printf("%s\n", envp[x]);
        x++;
    }
}
