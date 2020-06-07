#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
//创建一个模拟的http server
//绑定小端口号(<=1024) 需要root权限才能正常运行
//param(host,)

int main(int argc,char *argv[],char **env)
{
    //参数检查与初始化
    if(argc !=3) {
        fprintf(stderr,"usage: %s <domain ip address> <port name>\nFor example $ %s 127.0.0.1 80\n",argv[0],argv[0]);
        exit(0);
    }
    uint32_t host = 0;
    if(inet_pton(AF_INET,argv[1],&host) <= 0){
        fprintf(stderr,"domain ip address '%s' error\n",argv[1]);
        exit(0);
    }
    uint16_t port = (uint16_t)atoi(argv[2]);
    printf("setting server %s:%d\n",argv[1],port);
    port = htons(port);

    //打印 ruid,euid,suid
    uid_t ruid,euid,suid;
    getresuid(&ruid,&euid,&suid);
    printf("Process httpserver, pid=%d\truid=%d\teuid=%d\tsuid=%d\t \n",
            getpid(),ruid,euid,suid);
            
    //创建socket并绑定端口
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        perror("error when create socket");
        return -1;
    }
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = host;
    //绑定端口 若未设置suid 绑定小端口时会出现Permission denied
    if(bind(fd,(struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("error when binding socket");
        return -1;
    }
    printf("a root-only http server...\n");
    sleep(2);
    close(fd);
    return 0;
}