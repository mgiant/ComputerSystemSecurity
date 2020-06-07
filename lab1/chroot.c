#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    printf("Before chroot:\nruid=%d\teuid=%d\tsuid=%d\n", ruid, euid, suid);
    printf("change dir\n");
    //chdir("/chroot");
    printf("Change root\n");
    if(chroot("/chroot") == 0) {
        printf("change root succeed!\n");
    } else
    {
        perror("Change root error!");
        return 1;
    }
    printf("After chroot:\nruid=%d\teuid=%d\tsuid=%d\n", ruid, euid, suid);
    setresuid(ruid, ruid, ruid);
    getresuid(&ruid, &euid, &suid);
    printf("After cancel permission:\nruid=%d\teuid=%d\tsuid=%d\n", ruid, euid, suid);
    if(execl("/bin/bash", (char*)0)<0)
    {
        perror("error when execl bash");
        exit(0);
    }
    return 0;
}