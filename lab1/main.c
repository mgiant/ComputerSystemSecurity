#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    printf("Process main\npid=%d\truid=%d\teuid=%d\tsuid=%d\n", 
        getpid(), ruid, euid, suid);
    
    pid_t pid;

    // fork出一个子进程，执行fork程序
    if((pid = fork()) == 0) 
    {
        uid_t nruid, neuid, nsuid;
        getresuid(&nruid, &neuid, &nsuid);
        printf("Process fork\npid=%d\truid=%d\teuid=%d\tsuid=%d\n", 
            getpid(), nruid, neuid, nsuid);
        if(execl("./setuid.o",NULL)<0)
        {
            char * errnoMeg = strerror(errno);
            printf("Invoke setuid error! %s\n", errnoMeg);
        }
        return 0;
        
    }
    //等待子进程结束后再返回
    else 
    {
        int stat_val;
        waitpid(pid, &stat_val, 0);
    }
    return 0;
}