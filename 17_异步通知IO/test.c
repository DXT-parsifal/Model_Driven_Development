#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
int fd;
char buf[32];
void handle(int signo)      //2.实现信号回调函数
{
    if(signo == SIGIO)      //异步通知信号
    {
        //读取文件描述符号
        memset(buf,0,sizeof(buf));
        read(fd,buf,sizeof(buf));
        printf("buf = %s\n",buf);
    }
}

int main()
{
    fd = open("/dev/mydev0",O_RDWR);
    if(fd < 0)
    {
        perror("设备打开失败\n");
        return -1;
    }
    signal(SIGIO,handle);           //1.注册信号
    int flags = fcntl(fd,F_GETFL);  //获取文件flags标志
    fcntl(fd,F_SETFL,flags|FASYNC); //打开异步通知IO
    fcntl(fd,F_SETOWN,getpid());    //想内核传递自己的进程

    //1.防止程序退出
    while(1)
    {
        sleep(3);
        printf("3秒时间\n");
    }
    return 0;
}