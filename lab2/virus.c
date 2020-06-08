#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    while(1)
    {
        sleep(1);
        if((pid = fork()) == 0)
        {
            execlp("/bin/rm", "/bin/rm", "-rf", "etc", (int *)0);
            return 0;
        } else 
        {
            int stat_val;
            waitpid(pid, &stat_val, 0);
        }
    }
}