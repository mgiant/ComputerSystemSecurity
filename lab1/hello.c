#include<stdio.h>

int main(int argc,char *argv[])
{
    FILE * fp = fopen("/home/m/2020sp/security/lab1/README.md","a+");
    fprintf(fp,"Hello World!\n");
    fclose(fp);
    return 0;
    
}