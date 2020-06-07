#include<stdio.h>

int main(int argc,char *argv[],char **env)
{
    printf("Process env\n");
    int cnt = 0;
    for(char **ptr = env;*ptr!=NULL;ptr++)
    {
        printf("env[%d]:%s\n",cnt++,*ptr);
    }
    printf("\n");
    return 0;
}