#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    //打印 ruid,euid,suid
    uid_t ruid,euid,suid;
    getresuid(&ruid,&euid,&suid);
    uid_t pid = getpid();
    printf("Process setuid\npid=%d\truid=%d\teuid=%d\tsuid=%d\n",
            pid,ruid,euid,suid);
    
    if( (pid = fork())==0)
    {
        //int execl(const char *path, const char *arg, ...);
        if(execl("./server.o", "./server.o","127.0.0.1", "80",NULL)<0)
        {
            perror("error when execl http server");
            exit(0);
        }
    } else {
        int stat_val;
        waitpid(pid, &stat_val, 0);
    }
    //临时放弃权限
    setresuid(ruid, ruid, euid);
    printf("\nRevoke permission temporarily\n");
    getresuid(&ruid, &euid, &suid);
    printf("ruid=%d\teuid=%d\tsuid=%d\t\n", ruid, euid, suid);

    // execl与execle(有环境变量)的对比
    if( (pid = fork())==0)
    {
        //使用execl
        //int execl(const char *path, const char *arg, ...);
        if(execl("./env.o", NULL)<0)
        {
            perror("error when execl env.o");
        }
    } else {
        int stat_val;
        waitpid(pid, &stat_val, 0);
    }
    if( (pid = fork())==0)
    {
        //使用execle
        //int execle(const char *path, const char *arg,..., char * const envp[]);
        char* env[] = {"USER=m", "PATH=/home/m/2020sp/security/lab1/", NULL};
        if(execle("./env.o", NULL,env)<0)
        {
            perror("error when execle env.o");
            exit(0);
        }
    } else {
        int stat_val;
        waitpid(pid, &stat_val, 0);
    }
    
    // 恢复用户权限
    setresuid(ruid, suid, suid);
    printf("\nRestore permission \n");
    getresuid(&ruid, &euid, &suid);
    printf("ruid=%d\teuid=%d\tsuid=%d\t\n", ruid, euid, suid);
    
    if( (pid = fork())==0)
    {
        //int execl(const char *path, const char *arg, ...);
        if(execl("./server.o", "./server.o","127.0.0.1", "80",NULL)<0)
        {
            perror("error when execl the 2nd http server");
            exit(0);
        }
        
    } else {
        int stat_val;
        waitpid(pid, &stat_val, 0);
    }

    // 永久放弃权限
    setresuid(ruid, ruid, ruid);
    printf("\nRevoke permission permanently\n");
    getresuid(&ruid, &euid, &suid);
    printf("ruid=%d\teuid=%d\tsuid=%d\t\n", ruid, euid, suid);

    return 0;
}