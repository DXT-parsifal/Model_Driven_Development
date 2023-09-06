#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

//创建epoll对象 文件描述符对应内核中的红黑树
//int epoll_create(int __size)

//操作epoll对象  添加和删除
//int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

//询问epoll对象
//int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
//events:存储相应的文件描述符集
 
int main(int argc, char const *argv[])
{
    int epfd,fd,ret;
    struct epoll_event temp;//要操作文件的事件结构体
    struct epoll_event revr[10];//接收可用文件事件操作结构提
    char buf[32];
    epfd = epoll_create(10);
    fd = open("/dev/mydev0",O_RDWR);
    if(fd<0){
        perror("打开文件失败\n");
        return -1;
    }
    temp.data.fd = fd;//要打开的文件描述符
    temp.events=EPOLLIN;//读取事件
    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&temp);

    while(1){
        //轮训
        ret = epoll_wait(epfd,revr,10,3000);
        if(ret<=0){
            printf("3秒超时\n");
            continue;
        }
        //遍历可用事件的内容
        for(int i = 0;i<ret;i++){
            memset(buf,0,sizeof(buf));
            read(revr[i].data.fd,buf,sizeof(buf));
            printf("buf=%s\n",buf);
        }
    }

    return 0;
}
